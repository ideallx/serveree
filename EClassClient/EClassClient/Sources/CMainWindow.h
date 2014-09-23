#pragma once

#include "CDisplayDialog.h"
#include "CCommandDialog.h"
#include "CDrawDialog.h"

enum MainWindowDataType {
	M_LEFTDOWN,		// �������
	M_LEFTUP,		// ����ſ�
	M_PRESSMOVE,	// ��������ƶ�
	M_LEAVE,		// �뿪��Χ

	C_BEGIN,		// cmdָ�ʼ���
	C_CHANGESHAPE,	// �ı�ͼ��
	C_CHANGEPEN,	// �ı仭��
	C_CHANGEBRUSH	// �ı仭ˢ
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

	// �����²������ź�
	void ProcessMessage(ts_msg& msg, WPARAM wParam, LPARAM lParam, BOOL isremote);
};