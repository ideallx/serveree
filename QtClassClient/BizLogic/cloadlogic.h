#ifndef CLOADLOGIC_H
#define CLOADLOGIC_H

#include "CBaseLogic.h"

class CLoadLogic : public CBaseLogic
{
public:
    CLoadLogic(CMsgObject* parent = NULL);

    bool procMsg(const ts_msg& msg, bool isRemote);
};

#endif // CLOADLOGIC_H
