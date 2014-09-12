#include "CMainDialog.h"



CMainDialog::CMainDialog(CWnd* pParent)
	: CDisplayDialog(pParent) {

}

CMainDialog::~CMainDialog() {

}


BEGIN_MESSAGE_MAP(CMainDialog, CDisplayDialog)
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


void CMainDialog::OnMouseMove(UINT nFlags, CPoint point) {
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	TRACE("CPoint(%d, %d)\n", point.x, point.y);
	CDisplayDialog::OnMouseMove(nFlags, point);
}
