#pragma once

#include "../stdafx.h"

#include "CMsgReceiver.h"

#include <set>

using namespace std;

class CMsgSender {
protected:
	CMsgReceiver* p_MsgReceiver;

    set<CMsgReceiver*> receivers;

public:
	CMsgSender(void);
    virtual ~CMsgSender(void) {}

	// 成功加入返回true，若之前已存在，返回false
    bool addReceiver(CMsgReceiver* recv);

	// 成功移除返回true，若之前不存在，返回false
    bool removeReceiver(CMsgReceiver* recv);

public:
	// 发给某个具体的消息接收者
	virtual void sendMessage(CMsgReceiver* p_recv, const ts_msg& msg, 
		WPARAM wParam, LPARAM lParam, BOOL isremote = FALSE);
	
	// 发送给所有接收者
    virtual void sendToAll(const ts_msg& msg, WPARAM wParam, LPARAM lParam, BOOL isRemote = FALSE);
};
