#pragma once

#include "../stdafx.h"
#include <queue>
#include "../../../EBoardServer/EBoardServer/DataUnit/CMessage.h"

/****************************��Ϣ�ӿ�*******************************/
class CMsgReceiver
{
protected:
	UINT lastType;

public:
	CMsgReceiver(void) {};
	virtual ~CMsgReceiver(void) {};

public:
	// ����ģ�����յ�������
	virtual void ProcessMessage(ts_msg& msg, WPARAM wParam, LPARAM lParam, BOOL isremote) {};
};