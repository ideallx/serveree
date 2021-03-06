#include "CBaseLogic.h"

CSubSeqUnit::CSubSeqUnit()
    : wantedSeq(1)
    , minSeq(1) {
}

DWORD CSubSeqUnit::receiveMsg(const ts_msg& msg, map<TS_UINT64, ts_msg> &sendMap) {
    DWORD maxSubSeq = 0;
    TS_MESSAGE_HEAD* hmsg = (TS_MESSAGE_HEAD*) &msg;

    if (hmsg->subSeq < wantedSeq) {
        return 0;
    }

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

DWORD CSubSeqUnit::getMsgs(map<TS_UINT64, ts_msg>& sendMap) {
    DWORD maxSubSeq = 0;

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

// TODO better
bool CSubSeqUnit::getOldestMsg(ts_msg& msg) {
    msg = waitingList.begin()->second;
    waitingList.erase(waitingList.begin());

	if (waitingList.empty())
        return false;
    return true;
}

CBaseLogic::CBaseLogic(CMsgObject* parent)
    : CMsgObject(parent)
    , subseq(0) {
    ds = DataSingleton::getInstance();
}

CBaseLogic::~CBaseLogic() {


}

bool CBaseLogic::getOldestMsg(ts_msg& msg) {
    // get first table
    for (auto iter = userInfo.begin(); iter != userInfo.end(); ++iter) {
        TS_UINT64 uid = iter->first;
        CSubSeqUnit sub = iter->second;
        if (cache.find(uid) == cache.end()) {
            if (sub.hasNext()) {
                cache.insert(make_pair(getTime(msg), msg));
            }
        }
    }

    msg = cache.begin()->second;
    TS_UINT64 uid = getUid(msg);
    if (userInfo[uid].hasNext()) {
        ts_msg newMsg;
        userInfo[uid].getOldestMsg(newMsg);
        cache.insert(make_pair(getTime(newMsg), newMsg));
    }

    return !cache.empty();
}

bool CBaseLogic::procMsg(const ts_msg& msg, bool isRemote) {
    TS_MESSAGE_HEAD* hmsg = (TS_MESSAGE_HEAD*) &msg;

    if (!isRemote) {
        procNotRemote(msg);
        hmsg->subSeq = ++subseq;                    // so nice design!!!
        sendToDown(const_cast<ts_msg&> (msg), 0, 0, isRemote);
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
        if (hmsg->UID == ds->getUID())              // if you offline and online, you'll get your
            subseq = max(maxSubSeq, subseq);        // package sent before offline, and you'll get
        procRecvIsRemote(sendMap);                  // your last sub seq here
    }
    return false;
}

void CBaseLogic::procRecvIsRemote(map<TS_UINT64, ts_msg> sendMap) {
    for (auto i = sendMap.begin(); i != sendMap.end(); i++) {
        // TS_MESSAGE_HEAD* hmsg = (TS_MESSAGE_HEAD*) &i->second;
        //qDebug() << "send:" << hmsg->UID << hmsg->sequence << hmsg->subSeq;
        sendToUp(i->second, 0, 0, true);
    }
}
