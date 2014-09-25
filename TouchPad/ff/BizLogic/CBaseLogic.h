#pragma once

#include "../stdafx.h"

#include "../../../EBoardServer/EBoardServer/DataUnit/CMessage.h"
#include "CMsgObject.h"


class CBaseLogic : public CMsgObject {
private:

public:
	CBaseLogic(CMsgObject* parent = NULL);
	virtual ~CBaseLogic();

public:
	virtual void procMsg(const ts_msg& msg, bool isRemote) {};
};