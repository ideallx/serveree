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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	TRACE("CPoint(%d, %d)\n", point.x, point.y);
	CDisplayDialog::OnMouseMove(nFlags, point);
}
