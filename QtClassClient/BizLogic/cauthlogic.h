#ifndef CAUTHLOGIC_H
#define CAUTHLOGIC_H

#include "../Reliable/DataUnit/CMessage.h"
#include "CBaseLogic.h"

class CAuthLogic : public CBaseLogic
{
public:
    CAuthLogic(CMsgObject* parent = NULL);

    void procRecvIsRemote(map<TS_UINT64, ts_msg> sendMap);
};

#endif // CAUTHLOGIC_H
