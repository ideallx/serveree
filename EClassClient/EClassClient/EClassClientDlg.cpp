
// EClassClientDlg.cpp : 实现文件
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


// CEClassClientDlg 对话框

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


// CEClassClientDlg 消息处理程序

BOOL CEClassClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	SetBackgroundColor(RGB(183,229,32));
	// ShowWindow(SW_MAXIMIZE);		// 全屏

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CEClassClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CEClassClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


/**
	三层：  UI BL CN
*/
int CEClassClientDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码

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
	cn->addUpReceiver(bl);			// 三层，从上往下

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
