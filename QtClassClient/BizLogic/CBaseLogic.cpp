#include "CBaseLogic.h"

CSubSeqUnit::CSubSeqUnit() :
    wantedSeq(1) {
}

DWORD CSubSeqUnit::receiveMsg(const ts_msg& msg, map<TS_UINT64, ts_msg> &sendMap) {
    DWORD maxSubSeq = 0;
    TS_MESSAGE_HEAD* hmsg = (TS_MESSAGE_HEAD*) &msg;

    if (hmsg->subSeq == wantedSeq) {
        sendMap.insert(make_pair(hmsg->sequence, msg));
		maxSubSeq = hmsg->subSeq;
        wantedSeq++;
    } else {
        // qDebug() << "lost: " << wantedSeq << "from " << gmsg->head.UID;
        waitingList.insert(make_pair(hmsg->subSeq, msg));
    }

    while (true) {
        auto iter = waitingList.find(wantedSeq);
        if (iter == waitingList.end())
            break;
		sendMap.insert(make_pair(getSeq(iter->second), iter->second));
		maxSubSeq = ((TS_MESSAGE_HEAD*) &(iter->second))->subSeq;
        waitingList.erase(iter);
        wantedSeq++;
    }


    return maxSubSeq;
}


CBaseLogic::CBaseLogic(CMsgObject* parent) :
    CMsgObject(parent),
    subseq(0),
    ui(NULL),
    cn(NULL) {
}

CBaseLogic::~CBaseLogic() {


}

bool CBaseLogic::procMsg(const ts_msg& msg, bool isRemote) {
    TS_MESSAGE_HEAD* hmsg = (TS_MESSAGE_HEAD*) &msg;

    if (!ui)
        ui = static_cast<MainWindow*>(p_Parent->getAgent()->getModule("UI"));
    if (!cn)
        cn = static_cast<CClientNet*>(p_Parent->getAgent()->getModule("NET"));

    if (!isRemote) {
        procNotRemote(msg);
        hmsg->subSeq = ++subseq;                    // so nice design!!!
        qDebug() << "proc msg isnot remote" << hmsg->sequence << hmsg->subSeq;
        cn->ProcessMessage(const_cast<ts_msg&> (msg), 0, 0, isRemote);
        return false;
    } else {
        procIsRemote(msg);

        TS_UINT64 uid = hmsg->UID;
        if (userInfo.find(uid) == userInfo.end()) {
            CSubSeqUnit sub;
            userInfo.insert(make_pair(uid, sub));
        }

        map<TS_UINT64, ts_msg> sendMap;
        DWORD maxSubSeq = userInfo[uid].receiveMsg(msg, sendMap);
        if (hmsg->UID == globalUID)                 // if you offline and online, you'll get your
            subseq = max(maxSubSeq, subseq);        // package sent before offline, and you'll get
        procRecvIsRemote(sendMap);                  // your last sub seq here
    }
    return false;
}
