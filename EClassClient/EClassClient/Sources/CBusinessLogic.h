#pragma once

#include "../stdafx.h"
#include "CMsgObject.h"
#include "CUserLogic.h"

class CBusinessLogic : public CMsgObject {
private:
	CUserLogic* ul;

public:
	CBusinessLogic(CMsgObject* parent = NULL);
	virtual ~CBusinessLogic();

	// 接收外部模块的信号
	void ProcessMessage(ts_msg& msg, WPARAM wParam, LPARAM lParam, BOOL isremote);
private:


};