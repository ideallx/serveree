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

	// �ɹ����뷵��true����֮ǰ�Ѵ��ڣ�����false
    bool addUpReceiver(CMsgReceiver* recv);

    bool addDownReceiver(CMsgReceiver* recv);

	// �ɹ��Ƴ�����true����֮ǰ�����ڣ�����false
    bool removeUpReceiver(CMsgReceiver* recv);

    bool removeDownReceiver(CMsgReceiver* recv);

public:
	// ����ĳ���������Ϣ������
	virtual void sendMessage(CMsgReceiver* p_recv, const ts_msg& msg, 
		WPARAM wParam, LPARAM lParam, BOOL isremote = FALSE);
	
	// ���͸����н�����
    virtual void sendToUp(const ts_msg& msg, WPARAM wParam, LPARAM lParam, bool isRemote);

    virtual void sendToDown(const ts_msg& msg, WPARAM wParam, LPARAM lParam, bool isRemote);
};
