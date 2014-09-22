#pragma once

#include "CDisplayDialog.h"

class CCommandDialog : public CDisplayDialog {
public:
	CCommandDialog(CMsgObject* msgParent, CWnd* pParent = NULL);	// 标准构造函数
	virtual ~CCommandDialog();


};