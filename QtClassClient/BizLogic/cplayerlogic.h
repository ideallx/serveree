#ifndef CPLAYERLOGIC_H
#define CPLAYERLOGIC_H

#include "../Reliable/DataUnit/CMessage.h"
#include "CBaseLogic.h"
#include <map>

class CPlayerLogic : public CBaseLogic
{
public:
    CPlayerLogic(CMsgObject* parent = NULL);
    virtual ~CPlayerLogic() {}

    void procRecvIsRemote(map<TS_UINT64, ts_msg> sendMap);
};

#endif // CPLAYERLOGIC_H
