#pragma once

#include "../Reliable/DataUnit/CMessage.h"
#include "../Message/CMsgObject.h"


class CBaseLogic : public CMsgObject {
private:

public:
	CBaseLogic(CMsgObject* parent = NULL);
	virtual ~CBaseLogic();

public:
    // return true, dont send to another level
    virtual bool procMsg(const ts_msg& msg, bool isRemote);


};
