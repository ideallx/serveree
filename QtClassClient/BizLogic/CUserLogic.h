#pragma once

#include "CBaseLogic.h"
#include "../Message/CMsgObject.h"
#include "../Net/CClientNet.h"
#include "../Reliable/DataUnit/UserBase.h"


class CUserLogic : public CBaseLogic {
private:
	bool isLoggedIn;
    UserBase* ub;

public:
	CUserLogic(CMsgObject* msgParent);
	virtual ~CUserLogic();

    inline bool isServerAvailable() { return isLoggedIn; }

public:
    virtual bool procMsg(const ts_msg& msg, bool isRemote);
};
