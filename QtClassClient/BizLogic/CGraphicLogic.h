#ifndef CGRAPHICLOGIC_H
#define CGRAPHICLOGIC_H

#include "../Reliable/DataUnit/CMessage.h"
#include <map>
#include <QPointF>
#include <QMap>
#include "CBaseLogic.h"

using namespace std;

class CGraphicUserInfo {
public:
    CGraphicUserInfo();

    // return which to send
    // make sure the message sent was sorted
    map<TS_UINT64, ts_msg> receiveMsg(const ts_msg& msg);

private:
    DWORD wantedSeq;
    map<TS_UINT64, ts_msg> waitingList;             // seq -> ts_msg
};

class CGraphicLogic : public CBaseLogic
{
public:
    CGraphicLogic(CMsgObject* parent = NULL);
    virtual ~CGraphicLogic() {}

    virtual bool procMsg(const ts_msg& msg, bool isRemote);

private:
    DWORD subseq;
    map<TS_UINT64, CGraphicUserInfo> userInfo;     // uid -> userInfo
};

#endif // CGRAPHICLOGIC_H
