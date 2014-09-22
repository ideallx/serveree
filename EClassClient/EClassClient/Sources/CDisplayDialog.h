#pragma once

#include "../stdafx.h"
#include "../resource.h"		// 主符号
#include "afxdialogex.h"
#include "CMsgObject.h"


class CDisplayDialog : public CDialogEx {
	DECLARE_DYNAMIC(CDisplayDialog)

protected:
	CMsgObject* msgParent;

public:
	CDisplayDialog(CMsgObject* msgParent, CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDisplayDialog();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
