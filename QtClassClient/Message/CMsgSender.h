#pragma once

#include "../stdafx.h"

#include "CMsgReceiver.h"

#include <set>

using namespace std;

class CMsgSender {
protected:
	CMsgReceiver* p_MsgReceiver;

	set<CMsgReceiver*> upperReceivers;
	set<CMsgReceiver*> lowerReceivers;

public:
	CMsgSender(void);
    virtual ~CMsgSender(void) {}

	// �ɹ����뷵��true����֮ǰ�Ѵ��ڣ�����false
	bool addUpReceiver(CMsgReceiver* recv);
	bool addDownReceiver(CMsgReceiver* recv);

	// �ɹ��Ƴ�����true����֮ǰ�����ڣ�����false
	bool removeUpperReceiver(CMsgReceiver* recv);
	bool removeLowerReceiver(CMsgReceiver* recv);

public:
	// ����ĳ���������Ϣ������
	virtual void sendMessage(CMsgReceiver* p_recv, const ts_msg& msg, 
		WPARAM wParam, LPARAM lParam, BOOL isremote = FALSE);
	
	// ���͸����н�����
	virtual void sendToUpLayer(const ts_msg& msg, WPARAM wParam, LPARAM lParam, BOOL isRemote = FALSE);
	virtual void sendToDownLayer(const ts_msg& msg, WPARAM wParam, LPARAM lParam, BOOL isRemote = FALSE);

};
