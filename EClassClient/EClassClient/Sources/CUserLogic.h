#pragma once

#include "../stdafx.h"

#include "CBaseLogic.h"
#include "CMsgObject.h"


class CUserLogic : public CBaseLogic {
private:
	CMsgObject* msgParent;

public:
	CUserLogic(CMsgObject* msgParent);
	virtual ~CUserLogic();

public:
	virtual void procMsg(const ts_msg& msg);
};