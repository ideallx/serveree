#include "CBaseLogic.h"
#include "../LayerUI/mainwindow.h"
#include "../Net/CClientNet.h"

CSubSeqUnit::CSubSeqUnit() :
    wantedSeq(1) {
}

map<TS_UINT64, ts_msg> CSubSeqUnit::receiveMsg(const ts_msg& msg) {
    map<TS_UINT64, ts_msg> result;
    TS_MESSAGE_HEAD* hmsg = (TS_MESSAGE_HEAD*) &msg;

    if (hmsg->subSeq == wantedSeq) {
        result.insert(make_pair(hmsg->sequence, msg));
        wantedSeq++;
    } else {
        // qDebug() << "lost: " << wantedSeq << "from " << gmsg->head.UID;
        waitingList.insert(make_pair(hmsg->sequence, msg));
    }

    for (auto iter = waitingList.begin(); iter != waitingList.end(); ) {
        if (waitingList.size() == 0)
            break;

        if (iter->first == wantedSeq) {
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


CBaseLogic::CBaseLogic(CMsgObject* parent) :
    CMsgObject(parent),
    subseq(1)  {


}

CBaseLogic::~CBaseLogic() {


}

bool CBaseLogic::procMsg(const ts_msg& msg, bool isRemote) {
    MainWindow* ui = static_cast<MainWindow*>(p_Parent->getAgent()->getModule("UI"));
    CClientNet* cn = static_cast<CClientNet*>(p_Parent->getAgent()->getModule("NET"));
    TS_MESSAGE_HEAD* hmsg = (TS_MESSAGE_HEAD*) &msg;

    if (!isRemote) {
        procNotRemote(msg);

        hmsg->subSeq = subseq++;
        cn->ProcessMessage(const_cast<ts_msg&> (msg), 0, 0, isRemote);
        //qDebug() << "draw:" << gmsg->head.subSeq << "from" << gmsg->head.UID  << "on" << gmsg->SceneID << "total:" << ++ccccount;
        return false;
    } else {
        procIsRemote(msg);

        TS_UINT64 uid = hmsg->UID;
        if (userInfo.find(uid) == userInfo.end()) {
            CSubSeqUnit sub;
            userInfo.insert(make_pair(uid, sub));
        }

        auto sendMap = userInfo[uid].receiveMsg(msg);
        for (auto i = sendMap.begin(); i != sendMap.end(); i++) {
            ui->ProcessMessage(i->second, 0, 0, isRemote);
        }
    }
    return false;
}
