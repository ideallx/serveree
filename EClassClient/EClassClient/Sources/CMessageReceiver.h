#pragma once

#include "../stdafx.h"
/****************************消息接口*******************************/
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
	// 发给某个具体的消息接收者
	virtual void SendMessage(CMessageReceiver* p_recv, const TS_MESSAGE& msg, WPARAM wParam, LPARAM lParam, BOOL isremote = FALSE){
		if (!p_recv)
			return;

		p_recv->ProcessMessage(msg, wParam, lParam, isremote);
	};	
};

// Controller
// Object对象是一个即接受消息又发送消息的个体
// 任何对象都可能是消息的接受者和发送者
class CMsgObject:
	public CMessageSender, public CMessageReceiver
{
public:
	CMsgObject(void);
	virtual ~CMsgObject(void);
};

