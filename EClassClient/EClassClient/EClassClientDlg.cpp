
// EClassClientDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "EClassClient.h"
#include "EClassClientDlg.h"
#include "afxdialogex.h"

#include "Sources\CMainDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEClassClientDlg 对话框




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




int CEClassClientDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
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
