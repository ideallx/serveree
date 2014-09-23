#include "CDrawDialog.h"
#include "CShape.h"

CDrawDialog::CDrawDialog(CMsgObject* msgParent, CWnd* pParent)
	: CDisplayDialog(msgParent, pParent),
	isLeftPressed(false),
	sc(new CShapeCreator()) {

	ULONG_PTR m_gdiplusToken;
	Gdiplus::GdiplusStartupInput StartupInput;  
    GdiplusStartup(&m_gdiplusToken,&StartupInput,NULL);  
}

CDrawDialog::~CDrawDialog() {

}

BEGIN_MESSAGE_MAP(CDrawDialog, CDisplayDialog)
ON_WM_MOUSEMOVE()
ON_WM_MOUSELEAVE()
ON_WM_LBUTTONDOWN()
ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

void CDrawDialog::OnMouseMove(UINT nFlags, CPoint point) {
	if (isLeftPressed) {
		TS_GRAPHIC_PACKET msg;
		sc->generateGraphicsData(msg, point, FALSE);
		msgParent->ProcessMessage(*(ts_msg*) &msg, 0, 0, false);
	}

	CDisplayDialog::OnMouseMove(nFlags, point);
}


void CDrawDialog::OnMouseLeave()
{

	CDisplayDialog::OnMouseLeave();
}

static int clockoff = 0;
void CDrawDialog::OnLButtonDown(UINT nFlags, CPoint point)
{
	isLeftPressed = true;
	
	clockoff++;
	TS_GRAPHIC_PACKET msg;
	sc->create(clockoff % 4 + 1, point);
	sc->generateGraphicsData(msg, point, FALSE);
	msgParent->ProcessMessage(*(ts_msg*) &msg, 0, 0, false);

	CDisplayDialog::OnLButtonDown(nFlags, point);
}


void CDrawDialog::OnLButtonUp(UINT nFlags, CPoint point)
{
	isLeftPressed = false;
	
	TS_GRAPHIC_PACKET msg;
	sc->generateGraphicsData(msg, point, TRUE);
	msgParent->ProcessMessage(*(ts_msg*) &msg, 0, 0, false);

	CDisplayDialog::OnLButtonUp(nFlags, point);
}