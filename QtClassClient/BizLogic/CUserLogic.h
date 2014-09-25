#pragma once

#include "CBaseLogic.h"
#include "CMsgObject.h"
#include "CClientNet.h"
#include "../../../EBoardServer/EBoardServer/DataUnit/UserBase.h"


class CUserLogic : public CBaseLogic {
private:
	bool isLoggedIn;
	UserBase* ub;

	CClientNet* cn;

public:
	CUserLogic(CMsgObject* msgParent);
	virtual ~CUserLogic();

public:
	virtual void procMsg(const ts_msg& msg, bool isRemote);
};
