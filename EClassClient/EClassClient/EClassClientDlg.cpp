
// EClassClientDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "EClassClient.h"
#include "EClassClientDlg.h"
#include "afxdialogex.h"

#include "Sources\CDrawDialog.h"
#include "Sources\CCommandDialog.h"

#include "Sources\CBusinessLogic.h"
//#include "Sources\CCanvas.h"
#include "Sources\CClientNet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEClassClientDlg �Ի���

CEClassClientDlg::CEClassClientDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CEClassClientDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CEClassClientDlg::~CEClassClientDlg() {
	delete ui;
	delete cn;
	delete bl;
	WSACleanup();
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


/**
	���㣺  UI BL CN
*/
int CEClassClientDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������

	WSADATA wsadata;
    WSAStartup(MAKEWORD(2, 2), &wsadata);

	ui = new CMainWindow();
	bl = new CBusinessLogic();
	cn = new CClientNet();

	ma = CModuleAgent::getUniqueAgent();

	ma->registerModule("UI", ui);
	ma->registerModule("BIZ", bl);
	ma->registerModule("NET", cn);

	ui->addDownReceiver(bl);		// UI
	bl->addDownReceiver(cn);		// BL
	bl->addUpReceiver(ui);			// CN
	cn->addUpReceiver(bl);			// ���㣬��������

	unsigned char name[20] = "abcdefg";
	unsigned char pswd[20] = "hijklmn";
	UserBase* user = new UserBase();
	user->_classid = 10000;
	user->_reserved = 1;
	user->_role = RoleTeacher;
	user->_uid = 555;
	memcpy(user->_password, pswd, 20);
	memcpy(user->_username, name, 20);
// 	cn->setUser(*user);
	
	cn->SetServerAddr(0, "192.168.1.202", 2222);
	cn->Start(0);
	return 0;
}
