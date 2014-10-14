#ifndef CGRAPHICLOGIC_H
#define CGRAPHICLOGIC_H

#include <map>
#include <QPointF>
#include <QMap>
#include "CBaseLogic.h"

using namespace std;

class CGraphicUserInfo {
public:
    CGraphicUserInfo(DWORD firstSeq = 0);

    // return which to send
    // make sure the message sent was sorted
    map<TS_UINT64, ts_msg> receiveMsg(const ts_msg& msg);

private:
    DWORD lastShapeSeq;
    map<TS_UINT64, ts_msg> waitingList; // seq -> ts_msg
};

class CGraphicScenes {
public:
    CGraphicScenes() {}

    map<TS_UINT64, ts_msg> receiveMsg(const ts_msg& msg);

private:
    map<TS_UINT64, CGraphicUserInfo> userInfos;
};

class CGraphicLogic : public CBaseLogic
{
public:
    CGraphicLogic(CMsgObject* parent = NULL);
    virtual ~CGraphicLogic() {}

    virtual bool procMsg(const ts_msg& msg, bool isRemote);

private:
    map<TS_UINT64, CGraphicScenes> userInfo;     // uid -> userInfo
};

#endif // CGRAPHICLOGIC_H
