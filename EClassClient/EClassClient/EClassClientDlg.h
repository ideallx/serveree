
// EClassClientDlg.h : ͷ�ļ�
//

#pragma once
#include "Sources\CDisplayDialog.h"

// CEClassClientDlg �Ի���
class CEClassClientDlg : public CDialogEx
{
// ����
public:
	CEClassClientDlg(CWnd* pParent = NULL);	// ��׼���캯��
	virtual ~CEClassClientDlg();

// �Ի�������
	enum { IDD = IDD_ECLASSCLIENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;
	
	CDisplayDialog* commandDlg;
	CDisplayDialog* mainDlg;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};
