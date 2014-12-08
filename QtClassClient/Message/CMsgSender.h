#pragma once

#include "../stdafx.h"

#include "CMsgReceiver.h"
#include "../Reliable/DataStructure/TSQueue.h"

#include <set>


using namespace std;

class CMsgSender {
protected:
	CMsgReceiver* p_MsgReceiver;

    set<CMsgReceiver*> upReceivers;
    set<CMsgReceiver*> downReceivers;

    multimap<TS_UINT64, ts_msg> upCache;
    multimap<TS_UINT64, ts_msg> downCache;

public:
	CMsgSender(void);
    virtual ~CMsgSender(void) {}

	// 成功加入返回true，若之前已存在，返回false
    bool addUpReceiver(CMsgReceiver* recv);

    bool addDownReceiver(CMsgReceiver* recv);

	// 成功移除返回true，若之前不存在，返回false
    bool removeUpReceiver(CMsgReceiver* recv);

    bool removeDownReceiver(CMsgReceiver* recv);

public:
	// 发给某个具体的消息接收者
	virtual void sendMessage(CMsgReceiver* p_recv, const ts_msg& msg, 
		WPARAM wParam, LPARAM lParam, BOOL isremote = FALSE);
	
	// 发送给所有接收者
    virtual void sendToUp(const ts_msg& msg, WPARAM wParam, LPARAM lParam, bool isRemote);

    virtual void sendToDown(const ts_msg& msg, WPARAM wParam, LPARAM lParam, bool isRemote);
};
