#pragma once

#include "../stdafx.h"
#include <queue>
#include "../../../EBoardServer/EBoardServer/DataUnit/CMessage.h"

/****************************消息接口*******************************/
class CMsgReceiver
{
protected:
	UINT lastType;

public:
	CMsgReceiver(void) {};
	virtual ~CMsgReceiver(void) {};

public:
	// 处理模块外收到的数据
	virtual void ProcessMessage(ts_msg& msg, WPARAM wParam, LPARAM lParam, BOOL isremote) {};
};