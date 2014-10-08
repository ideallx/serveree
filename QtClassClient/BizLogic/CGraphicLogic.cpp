#include <QDebug>
#include "CGraphicLogic.h"
#include "mainwindow.h"
#include "../Net/CClientNet.h"

CGraphicUserInfo::CGraphicUserInfo() :
    lastShapeSeq(0) {

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
    }
    return result;
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
        CGraphicUserInfo user;
        userInfo.insert(make_pair(uid, user));
    }

    auto sendMap = userInfo[uid].receiveMsg(msg);
    for (auto i = sendMap.begin(); i != sendMap.end(); i++) {
        ui->ProcessMessage(i->second, gmsg->graphicsType, 0, isRemote);
    }

    return false;
}
