#pragma once

#include "CDisplayDialog.h"
#include "CCommandDialog.h"
#include "CDrawDialog.h"

enum MainWindowDataType {
	M_LEFTDOWN,		// 左键按下
	M_LEFTUP,		// 左键放开
	M_PRESSMOVE,	// 按着左键移动
	M_LEAVE,		// 离开范围

	C_BEGIN,		// cmd指令开始标记
	C_CHANGESHAPE,	// 改变图形
	C_CHANGEPEN,	// 改变画笔
	C_CHANGEBRUSH	// 改变画刷
};


class CMainWindow : public CMsgObject {
private:
	CCommandDialog* ccd;

	UINT curShape;

public:
	CDrawDialog* cmd;

	CMainWindow(CWnd* pParent = NULL, CMsgObject pMsgParent = NULL);
	virtual ~CMainWindow();

	void loginSuccess();

	void actCreate();

	inline void draw();

	// 接收下层来的信号
	void ProcessMessage(ts_msg& msg, WPARAM wParam, LPARAM lParam, BOOL isremote);
};