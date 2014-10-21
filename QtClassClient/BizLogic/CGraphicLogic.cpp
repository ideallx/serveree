#include <QDebug>
#include "CGraphicLogic.h"
#include "../LayerUI/mainwindow.h"
#include "../Net/CClientNet.h"

CGraphicUserInfo::CGraphicUserInfo(DWORD firstSeq) :
    wantedSeq(1) {
}

static int ccccount = 0;
map<TS_UINT64, ts_msg> CGraphicUserInfo::receiveMsg(const ts_msg& msg) {
    map<TS_UINT64, ts_msg> result;
    TS_GRAPHIC_PACKET* gmsg = (TS_GRAPHIC_PACKET*) &msg;
    qDebug() << "recv:" << gmsg->head.subSeq << "from" << gmsg->head.UID << "total:" << ++ccccount;

    if (gmsg->head.subSeq == wantedSeq) {
        result.insert(make_pair(gmsg->head.sequence, msg));
        wantedSeq++;
    } else {
        //qDebug() << "lost: " << wantedSeq << "from " << gmsg->head.UID;
        waitingList.insert(make_pair(gmsg->head.sequence, msg));
    }

    for (auto iter = waitingList.begin(); iter != waitingList.end(); ) {
        if (waitingList.size() == 0)
            break;

        if (iter->first == wantedSeq) {
            //qDebug() << "recv: " << wantedSeq << "from " << gmsg->head.UID;
            result.insert(make_pair(iter->first, iter->second));
            waitingList.erase(iter++);
            wantedSeq++;
        } else if (iter->first < wantedSeq) {
            iter++;
        } else {
            break;
        }
    }
    return result;
}

map<TS_UINT64, ts_msg> CGraphicScenes::receiveMsg(const ts_msg& msg) {
    TS_GRAPHIC_PACKET* gmsg = (TS_GRAPHIC_PACKET*) &msg;
    DWORD sceneID = gmsg->SceneID;

    if (sceneID == globalUID) {
		gmsg->SceneID = sceneID = SelfUID;
	} else if (sceneID == SelfUID) {
        gmsg->SceneID = sceneID = gmsg->head.UID;
	}

    if (userInfos.find(sceneID) == userInfos.end()) {
        CGraphicUserInfo user(gmsg->head.subSeq);
        userInfos.insert(make_pair(sceneID, user));
    }

    return userInfos[sceneID].receiveMsg(msg);
}


CGraphicLogic::CGraphicLogic(CMsgObject *parent) :
    CBaseLogic(parent),
    subseq(1) {
}

bool CGraphicLogic::procMsg(const ts_msg& msg, bool isRemote) {
    MainWindow* ui = static_cast<MainWindow*>(p_Parent->getAgent()->getModule("UI"));
    CClientNet* cn = static_cast<CClientNet*>(p_Parent->getAgent()->getModule("NET"));

    if (!isRemote) {
        TS_GRAPHIC_PACKET* gmsg = (TS_GRAPHIC_PACKET*) &msg;
        gmsg->head.subSeq = subseq++;
        cn->ProcessMessage(const_cast<ts_msg&> (msg), 0, 0, isRemote);
        return false;
    }

    TS_GRAPHIC_PACKET* gmsg = (TS_GRAPHIC_PACKET*) &msg;
    TS_UINT64 uid = gmsg->head.UID;
    if (userInfo.find(uid) == userInfo.end()) {
        CGraphicScenes scene;
        userInfo.insert(make_pair(uid, scene));
    }

    auto sendMap = userInfo[uid].receiveMsg(msg);
    for (auto i = sendMap.begin(); i != sendMap.end(); i++) {
        ui->ProcessMessage(i->second, gmsg->graphicsType, 0, isRemote);
    }

    return false;
}
