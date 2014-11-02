#ifndef CFILELOGIC_H
#define CFILELOGIC_H

#include "../Reliable/DataUnit/CMessage.h"
#include "CBaseLogic.h"

class CFileLogic : public CBaseLogic
{
public:
    CFileLogic(CMsgObject* parent = NULL);
    virtual ~CFileLogic() {}

    virtual bool procMsg(const ts_msg& msg, bool isRemote);
};

#endif // CFILELOGIC_H
