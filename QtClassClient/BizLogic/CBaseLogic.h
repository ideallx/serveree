#pragma once

#include "../LayerUI/mainwindow.h"
#include "../Reliable/DataUnit/CMessage.h"
#include "../Message/CMsgObject.h"
#include "datasingleton.h"

class CSubSeqUnit {
public:
    CSubSeqUnit();

    // TODO new logic to replace the map!!!
    // return which to send
    // make sure the message sent was sorted
    DWORD receiveMsg(const ts_msg& msg, map<TS_UINT64, ts_msg>& sendMap);

    DWORD getMsgs(map<TS_UINT64, ts_msg>& sendMap);

    bool getOldestMsg(ts_msg& msg);

    inline bool hasNext() { return !waitingList.empty(); }

private:
    DWORD wantedSeq;
    TS_UINT64 minSeq;
    map<TS_UINT64, ts_msg> waitingList;
    // map<TS_UINT64, ts_msg> waitingList;             // seq -> ts_msg
};

class CBaseLogic : public CMsgObject {
private:

public:
	CBaseLogic(CMsgObject* parent = NULL);
	virtual ~CBaseLogic();

protected:
    DWORD subseq;
    map<TS_UINT64, CSubSeqUnit> userInfo;       // uid -> userInfo
    map<TS_UINT64, ts_msg> cache;               // time -> msg
    DataSingleton* ds;

public:
    // get oldest msg from waitinglist, return true shows that there still has msgs
    virtual bool getOldestMsg(ts_msg& msg);

    // return true, dont send to another level
    virtual bool procMsg(const ts_msg& msg, bool isRemote);

    virtual void procIsRemote(const ts_msg& msg) { Q_UNUSED(msg); }
    virtual void procRecvIsRemote(map<TS_UINT64, ts_msg> sendMap);

    virtual void procNotRemote(const ts_msg& msg) { Q_UNUSED(msg); }
    virtual void procRecvNotRemote(const ts_msg& msg) { Q_UNUSED(msg); }
};
