
// EClassClient.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once
#include "stdafx.h"
#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CEClassClientApp:
// �йش����ʵ�֣������ EClassClient.cpp
//

class CEClassClientApp : public CWinApp
{
public:
	CEClassClientApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CEClassClientApp theApp;