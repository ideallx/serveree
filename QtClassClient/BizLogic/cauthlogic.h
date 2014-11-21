#ifndef CAUTHLOGIC_H
#define CAUTHLOGIC_H

#include "../Reliable/DataUnit/CMessage.h"
#include "CBaseLogic.h"

class CAuthLogic : public CBaseLogic
{
public:
    CAuthLogic(CMsgObject* parent = NULL);
};

#endif // CAUTHLOGIC_H
