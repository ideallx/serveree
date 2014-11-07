#include "CBaseLogic.h"

CSubSeqUnit::CSubSeqUnit() :
    wantedSeq(1) {
}

DWORD CSubSeqUnit::receiveMsg(const ts_msg& msg, map<TS_UINT64, ts_msg> &sendMap) {
    const ts_msg* lastMsg = NULL;
    TS_MESSAGE_HEAD* hmsg = (TS_MESSAGE_HEAD*) &msg;

    if (hmsg->subSeq == wantedSeq) {
        sendMap.insert(make_pair(hmsg->sequence, msg));
        lastMsg = &msg;
        wantedSeq++;
    } else {
        // qDebug() << "lost: " << wantedSeq << "from " << gmsg->head.UID;
        waitingList.insert(make_pair(hmsg->sequence, msg));
    }

    while (true) {
        auto iter = waitingList.find(wantedSeq);
        if (iter == waitingList.end())
            break;
        sendMap.insert(make_pair(iter->first, iter->second));
        waitingList.erase(iter);
        wantedSeq++;
        lastMsg = &(iter->second);
    }

    if (lastMsg == NULL) {
        return 0;
    } else {
        return ((TS_MESSAGE_HEAD*) lastMsg)->subSeq;
    }
}


CBaseLogic::CBaseLogic(CMsgObject* parent) :
    CMsgObject(parent),
    subseq(1),
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
        hmsg->subSeq = subseq++;                    // so nice design!!!
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
