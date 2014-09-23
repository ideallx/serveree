#include "CMainWindow.h"

CMainWindow::CMainWindow(CWnd* pParent, CMsgObject pMsgParent):
	CMsgObject(pMsgParent),
	cmd(NULL),
	ccd(NULL),
	curShape(NONE) {
	int screenwidth=GetSystemMetrics(SM_CXSCREEN);
	int screenheight=GetSystemMetrics(SM_CYSCREEN);

	cmd = new CDrawDialog(this, pParent);
	ccd = new CCommandDialog(this, pParent);
	
	CDisplayDialog* up = cmd;
	int upSize = 500;

	CDisplayDialog* down = ccd;
	int downSize = 5;

	up->Create(IDD_DIALOG1, pParent);
	up->SetBackgroundColor(RGB(154, 217, 234));
	//ccd->MoveWindow(0, 0, screenwidth, 100);
	up->MoveWindow(0, 0, upSize, upSize);
	up->ShowWindow(SW_SHOW);

	down->Create(IDD_DIALOG1, pParent);
	down->SetBackgroundColor(RGB(255, 201, 13));
	//cmd->MoveWindow(0, 110, screenwidth, screenheight - 110);
	down->MoveWindow(0, 510, downSize, downSize);
	down->ShowWindow(SW_SHOW);
}


CMainWindow::~CMainWindow() {
	delete cmd;
	delete ccd;
}

void CMainWindow::ProcessMessage(ts_msg& msg, WPARAM wParam, LPARAM lParam, BOOL isRemote) {
	//if (isremote) {
	//	TS_GRAPHIC_PACKET* packet = (TS_GRAPHIC_PACKET*) &msg;
	//	if (packet->data.DoneFlag) {
	//		cmd->actMoveEnd(*packet);
	//	} else {
	//		cmd->actMove(*packet);
	//	}
	//} else {
	//	sendToDownLayer(*(ts_msg*) &msg, 0, 0, false);		// 发给下层
	//}
	if (!isRemote) {
		sendToDownLayer(*(ts_msg*) &msg, 0, 0, false);		// 发给下层
	}
}