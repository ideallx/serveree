#include "../EClassClient.h"
#include "CDisplayDialog.h"


// MyDialog 对话框

IMPLEMENT_DYNAMIC(CDisplayDialog, CDialogEx)

CDisplayDialog::CDisplayDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDisplayDialog::IDD, pParent) {

}

CDisplayDialog::~CDisplayDialog() {
}

void CDisplayDialog::DoDataExchange(CDataExchange* pDX) {
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDisplayDialog, CDialogEx)
END_MESSAGE_MAP()


// MyDialog 消息处理程序