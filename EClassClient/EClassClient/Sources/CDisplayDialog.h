#pragma once

#include "../stdafx.h"
#include "../resource.h"		// ������
#include "afxdialogex.h"


class CDisplayDialog : public CDialogEx {
	DECLARE_DYNAMIC(CDisplayDialog)

public:
	CDisplayDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDisplayDialog();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
