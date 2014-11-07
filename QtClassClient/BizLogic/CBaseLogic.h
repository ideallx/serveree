#pragma once

#include "../LayerUI/mainwindow.h"
#include "../Net/CClientNet.h"
#include "../Reliable/DataUnit/CMessage.h"
#include "../Message/CMsgObject.h"

class CSubSeqUnit {
public:
    CSubSeqUnit();

    // return which to send
    // make sure the message sent was sorted
    DWORD receiveMsg(const ts_msg& msg, map<TS_UINT64, ts_msg>& sendMap);

private:
    DWORD wantedSeq;
    map<TS_UINT64, ts_msg> waitingList;             // seq -> ts_msg
};

class CBaseLogic : public CMsgObject {
private:

public:
	CBaseLogic(CMsgObject* parent = NULL);
	virtual ~CBaseLogic();

protected:
    DWORD subseq;
    map<TS_UINT64, CSubSeqUnit> userInfo;     // uid -> userInfo
    MainWindow* ui;
    CClientNet* cn;

public:
    // return true, dont send to another level
    virtual bool procMsg(const ts_msg& msg, bool isRemote);

    virtual void procIsRemote(const ts_msg& msg) {}
    virtual void procRecvIsRemote(map<TS_UINT64, ts_msg> sendMap) {}

    virtual void procNotRemote(const ts_msg& msg) {}
    virtual void procRecvNotRemote(const ts_msg& msg) {}
};
