#include <QDebug>
#include "CGraphicLogic.h"
#include "mainwindow.h"
#include "../Net/CClientNet.h"

CGraphicUserInfo::CGraphicUserInfo(DWORD firstSeq) :
    lastShapeSeq(firstSeq) {
}

map<TS_UINT64, ts_msg> CGraphicUserInfo::receiveMsg(const ts_msg& msg) {
    map<TS_UINT64, ts_msg> result;
    TS_GRAPHIC_PACKET* gmsg = (TS_GRAPHIC_PACKET*) &msg;

    if (gmsg->head.subSeq == lastShapeSeq + 1) {
        result.insert(make_pair(gmsg->head.sequence, msg));
        lastShapeSeq++;
        if (waitingList.size() != 0) {
            for (auto i = waitingList.begin(); i != waitingList.end(); ) {
                TS_UINT64 waitSeq = getSeq(i->second);
                if (waitSeq == lastShapeSeq + 1) {
                    result.insert(make_pair(waitSeq, i->second));
                    waitingList.erase(i++);
                } else {
                    break;
                }
            }
        }
    } else {
        waitingList.insert(make_pair(gmsg->head.sequence, msg));
        qDebug() << gmsg->head.UID << "recv:" << gmsg->head.subSeq << "wait for:" << lastShapeSeq + 1;
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
    CBaseLogic(parent) {
}

bool CGraphicLogic::procMsg(const ts_msg& msg, bool isRemote) {
    MainWindow* ui = static_cast<MainWindow*>(p_Parent->getAgent()->getModule("UI"));
    CClientNet* cn = static_cast<CClientNet*>(p_Parent->getAgent()->getModule("NET"));

    if (!isRemote) {
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
