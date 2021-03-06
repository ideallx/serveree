#pragma once


#include "CMsgReceiver.h"
#include "CMsgSender.h"
#include "CModuleAgent.h"

// Controller
// Object对象是一个即接受消息又发送消息的个体
// 任何对象都可能是消息的接受者和发送者

class CMsgObject : public CMsgSender, public CMsgReceiver {
protected:
    CModuleAgent* p_agent;

	CMsgObject* p_Parent;
	set<CMsgObject*> p_ChildList;



public:
	CMsgObject(CMsgObject* parent = NULL);

	virtual ~CMsgObject(void);


public:
    void setAgent(CModuleAgent* agent);

    inline CModuleAgent* getAgent() { return p_agent; }

	CMsgObject* getAncestor();

	void changeParent(CMsgObject* newParent);

	void sendToUp(const ts_msg& msg, WPARAM wParam, LPARAM lParam, bool isRemote);

	void sendToDown(const ts_msg& msg, WPARAM wParam, LPARAM lParam, bool isRemote);

private:
	void removeChild(CMsgObject* child);

	void addChild(CMsgObject* obj);
};
