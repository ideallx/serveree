#include "../EClassClient.h"
#include "CDisplayDialog.h"


// MyDialog 对话框

IMPLEMENT_DYNAMIC(CDisplayDialog, CDialogEx)

CDisplayDialog::CDisplayDialog(CMsgObject* msgParent, CWnd* pParent) : 
	CDialogEx(CDisplayDialog::IDD, pParent),
	msgParent(msgParent) {
}

CDisplayDialog::~CDisplayDialog() {

}

void CDisplayDialog::DoDataExchange(CDataExchange* pDX) {
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDisplayDialog, CDialogEx)
END_MESSAGE_MAP()


// MyDialog 消息处理程序