#pragma once

#include "CDisplayDialog.h"

class CMainDialog : public CDisplayDialog {
public:
	CMainDialog(CWnd* pParent = NULL);	// ��׼���캯��
	virtual ~CMainDialog();


	DECLARE_MESSAGE_MAP()
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};