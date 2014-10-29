#include <QDebug>
#include "CGraphicLogic.h"
#include "../LayerUI/mainwindow.h"
#include "../Net/CClientNet.h"

CGraphicUserInfo::CGraphicUserInfo() :
    wantedSeq(1) {
}

static int ccccount = 0;
map<TS_UINT64, ts_msg> CGraphicUserInfo::receiveMsg(const ts_msg& msg) {
    map<TS_UINT64, ts_msg> result;
    TS_GRAPHIC_PACKET* gmsg = (TS_GRAPHIC_PACKET*) &msg;

    if (gmsg->head.subSeq == wantedSeq) {
        //qDebug() << "draw:" << wantedSeq << "from" << gmsg->head.UID  << "on" << gmsg->SceneID << "total:" << ++ccccount;
        result.insert(make_pair(gmsg->head.sequence, msg));
        wantedSeq++;
    } else {
        // qDebug() << "lost: " << wantedSeq << "from " << gmsg->head.UID;
        waitingList.insert(make_pair(gmsg->head.sequence, msg));
    }

    for (auto iter = waitingList.begin(); iter != waitingList.end(); ) {
        if (waitingList.size() == 0)
            break;

        if (iter->first == wantedSeq) {
            //qDebug() << "draw:" << wantedSeq << "from" << gmsg->head.UID  << "on" << gmsg->SceneID << "total:" << ++ccccount;
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
        //qDebug() << "draw:" << gmsg->head.subSeq << "from" << gmsg->head.UID  << "on" << gmsg->SceneID << "total:" << ++ccccount;
        return false;
    }

    TS_GRAPHIC_PACKET* gmsg = (TS_GRAPHIC_PACKET*) &msg;

    if (gmsg->SceneID == globalUID) {
        gmsg->SceneID = SelfUID;
    } else if (gmsg->SceneID == SelfUID) {
        gmsg->SceneID = gmsg->head.UID;
    }

    TS_UINT64 uid = gmsg->head.UID;
    if (userInfo.find(uid) == userInfo.end()) {
        CGraphicUserInfo ui;
        userInfo.insert(make_pair(uid, ui));
    }

    auto sendMap = userInfo[uid].receiveMsg(msg);
    for (auto i = sendMap.begin(); i != sendMap.end(); i++) {
        ui->ProcessMessage(i->second, 0, 0, isRemote);
    }

    return false;
}
