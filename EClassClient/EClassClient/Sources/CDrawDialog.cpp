#include "CDrawDialog.h"
#include "CShape.h"

CDrawDialog::CDrawDialog(CMsgObject* msgParent, CWnd* pParent)
	: CDisplayDialog(msgParent, pParent),
	isLeftPressed(false),
	sp(new CShapePage()),
	sc(new CShapeCreator()) {

	ULONG_PTR m_gdiplusToken;
	Gdiplus::GdiplusStartupInput StartupInput;  
    GdiplusStartup(&m_gdiplusToken,&StartupInput,NULL);  

	pt = new CPaintTools();
	sc->setPaintTool(pt);
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
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	TRACE("CPoint(%d, %d)\n", point.x, point.y);
	
	TS_GRAPHIC_PACKET msg;
	if (isLeftPressed) {
		// actMove(point);
		sc->generateGraphicsData(msg, point, FALSE);
		msgParent->ProcessMessage(*(ts_msg*) &msg, 0, 0, false);
		actMove(msg);
	}

	CDisplayDialog::OnMouseMove(nFlags, point);
}


void CDrawDialog::OnMouseLeave()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDisplayDialog::OnMouseLeave();
}

static int clockff = 0;
void CDrawDialog::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	isLeftPressed = true;
	
	//actCreate(SCRIPTS);

	TS_GRAPHIC_PACKET msg;

	clockff++;
	sc->create(clockff % 4 + 1, pt, point);

	sc->generateGraphicsData(msg, point, FALSE);
	msgParent->ProcessMessage(*(ts_msg*) &msg, 0, 0, false);

	sp->setBeginPoint(Point(point.x, point.y));
	actMove(msg);

	CDisplayDialog::OnLButtonDown(nFlags, point);
}


void CDrawDialog::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	isLeftPressed = false;
	
	TS_GRAPHIC_PACKET msg;
	sc->generateGraphicsData(msg, point, TRUE);
	msgParent->ProcessMessage(*(ts_msg*) &msg, 0, 0, false);
	actMoveEnd(msg);

	CDisplayDialog::OnLButtonUp(nFlags, point);
}


void CDrawDialog::actMove(TS_GRAPHIC_PACKET& msg) {
	sp->MakeShape(msg, pt);
}


void CDrawDialog::actMoveEnd(TS_GRAPHIC_PACKET& msg) {
	CShape* s = sp->MakeShape(msg, pt);
	if (NULL != s) {
		CDC* c = GetDC();
		Graphics g(c->m_hDC);
		CRect r;
		GetClientRect(&r);
		Bitmap bmp(r.Width(), r.Height());
		Graphics * grp = Graphics::FromImage(&bmp);

		sp->Draw(grp, pt, 0, 0);
		g.DrawImage(&bmp, 0, 0);
		ReleaseDC(c);
	}
}