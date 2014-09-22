
// EClassClientDlg.h : ͷ�ļ�
//

#pragma once
#include "Sources\CMainWindow.h"
#include "Sources\CClientNet.h"
#include "Sources\CBusinessLogic.h"
#include "Sources\CModuleAgent.h"

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
	
	CMainWindow* ui;
	CClientNet* cn;
	CBusinessLogic* bl;
	CModuleAgent* ma;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};
