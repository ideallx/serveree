#pragma once

#include "../stdafx.h"
/****************************��Ϣ�ӿ�*******************************/
class CMessageReceiver
{
public:
	CMessageReceiver(void){};
	virtual ~CMessageReceiver(void){};

public:
	virtual void ProcessMessage(const TS_MESSAGE& msg, WPARAM wParam, LPARAM lParam, BOOL isremote){};
};

class CMessageSender{
protected:
	CMessageReceiver* p_MsgReceiver;

public:
	CMessageSender(void){
		p_MsgReceiver = NULL;
	};
	virtual ~CMessageSender(void){};

public:
	// ����ĳ���������Ϣ������
	virtual void SendMessage(CMessageReceiver* p_recv, const TS_MESSAGE& msg, WPARAM wParam, LPARAM lParam, BOOL isremote = FALSE){
		if (!p_recv)
			return;

		p_recv->ProcessMessage(msg, wParam, lParam, isremote);
	};	
};

// Controller
// Object������һ����������Ϣ�ַ�����Ϣ�ĸ���
// �κζ��󶼿�������Ϣ�Ľ����ߺͷ�����
class CMsgObject:
	public CMessageSender, public CMessageReceiver
{
public:
	CMsgObject(void);
	virtual ~CMsgObject(void);
};

