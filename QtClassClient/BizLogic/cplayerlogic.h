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
};

#endif // CPLAYERLOGIC_H
