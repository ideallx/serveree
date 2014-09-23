#pragma once

#include "CGraphicLogic.h"

CGraphicLogic::CGraphicLogic(CMsgObject* msgParent) :
	CBaseLogic(msgParent),
	p_DrawingCanvas(new CWinCanvas),
	p_DrawedCanvas(new CWinCanvas),
	p_DrawingShape(new CShapeStage),
	p_DrawedShape(new CShapePage),
	p_PaintTool(new CPaintTools),
	p_UI(NULL) {

}

CGraphicLogic::~CGraphicLogic() {
	delete p_DrawingCanvas;
	delete p_DrawedCanvas;
	delete p_DrawingShape;
	delete p_DrawedShape;
	delete p_PaintTool;
	delete p_UI;
}


void CGraphicLogic::initial() {
	if (NULL == p_UI) {			// initial
		p_UI = static_cast<CMainWindow*>(p_Parent->getAgent()->getModule("UI"));
		CRect r;
		GetClientRect(p_UI->cmd->m_hWnd, &r);
		p_DrawedCanvas->Create(p_UI->cmd->GetDC()->m_hDC, r.Width(), r.Height());
		p_DrawingCanvas->Create(p_UI->cmd->GetDC()->m_hDC, r.Width(), r.Height());

	}
}

void CGraphicLogic::procMsg(const ts_msg& msg, bool isRemote) {
	initial();
	TS_GRAPHIC_PACKET* packet = (TS_GRAPHIC_PACKET*) &msg;
	if (packet->data.DoneFlag) {
		CShape* s = p_DrawedShape->MakeShape(*packet, p_PaintTool);
		if (NULL != s) {
			Graphics* g = p_DrawedCanvas->GetCanvasGraphic();
			
			Bitmap bmp(500, 500);
			Graphics *grp = Graphics::FromImage(&bmp);
			
			p_DrawedShape->Draw(g, p_PaintTool, 0, 0);
			p_DrawedCanvas->Draw(g, 0, 0);


			p_DrawedCanvas->FillBackground(-1);

			//p_DrawingCanvas->Draw(grp, 0, 0);
			//p_DrawingCanvas->Clear();
			//delete grp;
		}
	} else {
		p_DrawedShape->MakeShape(*packet, p_PaintTool);
		//CShape* shape = p_DrawingShape->FindShape(packet->head.UID);
		//if (shape == NULL) {
		//	shape = p_DrawedShape->MakeShape(*packet, p_PaintTool);
		//}
		//shape->addPoint(packet->data.ShapeSeq, 
		//	&Point(packet->data.BeginPx, packet->data.BeginPy),
		//	&Point(packet->data.PointX, packet->data.PointY));

		//Graphics * grp = Graphics::FromHDC(p_DrawingCanvas->GetCanvasDC());
		//p_DrawingShape->Draw(grp, p_PaintTool, 0, 0);
	}
}