
// EClassClientDlg.h : 头文件
//

#pragma once
#include "Sources\CDisplayDialog.h"

// CEClassClientDlg 对话框
class CEClassClientDlg : public CDialogEx
{
// 构造
public:
	CEClassClientDlg(CWnd* pParent = NULL);	// 标准构造函数
	virtual ~CEClassClientDlg();

// 对话框数据
	enum { IDD = IDD_ECLASSCLIENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	
	CDisplayDialog* commandDlg;
	CDisplayDialog* mainDlg;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};
