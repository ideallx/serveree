#pragma once

#include "../Reliable/DataUnit/CMessage.h"
#include "CBaseLogic.h"
#include "../Reliable/DataUnit/UserBase.h"
#include "datasingleton.h"


// bool isLoggedIn should be deprecated for it is recorded in DataSingleton now
class CUserLogic : public CBaseLogic {
private:
    UserBase* ub;

public:
	CUserLogic(CMsgObject* msgParent);
	virtual ~CUserLogic();

    inline bool isServerAvailable() { return ds->isLoggedIn(); }

public:
    virtual bool procMsg(const ts_msg& msg, bool isRemote);
};
