
// EClassClientDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "EClassClient.h"
#include "EClassClientDlg.h"
#include "afxdialogex.h"

#include "Sources\CMainDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEClassClientDlg �Ի���




CEClassClientDlg::CEClassClientDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CEClassClientDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	commandDlg = new CDisplayDialog(this);
	mainDlg = new CMainDialog(this);
}

CEClassClientDlg::~CEClassClientDlg() {
	delete commandDlg;
	delete mainDlg;
}

void CEClassClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CEClassClientDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CREATE()
END_MESSAGE_MAP()


// CEClassClientDlg ��Ϣ�������

BOOL CEClassClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	SetBackgroundColor(RGB(183,229,32));
	// ShowWindow(SW_MAXIMIZE);		// ȫ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CEClassClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CEClassClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}




int CEClassClientDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	int screenwidth=GetSystemMetrics(SM_CXSCREEN);
	int screenheight=GetSystemMetrics(SM_CYSCREEN);

	commandDlg->Create(IDD_DIALOG1, this);
	commandDlg->SetBackgroundColor(RGB(154, 217, 234));
	// commandDlg.MoveWindow(0, 0, screenwidth, 100);
	commandDlg->MoveWindow(0, 0, 100, 100);
	commandDlg->ShowWindow(SW_SHOW);

	mainDlg->Create(IDD_DIALOG1, this);
	mainDlg->SetBackgroundColor(RGB(255, 201, 13));
	//mainDlg.MoveWindow(0, 110, screenwidth, screenheight - 110);
	mainDlg->MoveWindow(0, 110, 100, 300 - 110);
	mainDlg->ShowWindow(SW_SHOW);
	return 0;
}
