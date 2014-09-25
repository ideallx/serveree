#pragma once

#include "../stdafx.h"

#include "CBaseLogic.h"
#include "CMsgObject.h"

#include "CCanvas.h"
#include "CShapeContainer.h"
#include "CShape.h"
#include "CMainWindow.h"


class CGraphicLogic : public CBaseLogic {
private:
	CCanvas*		p_DrawingCanvas;
	CCanvas*		p_DrawedCanvas;

	CShapeStage*	p_DrawingShape;
	CShapePage*		p_DrawedShape;
	CPaintTools*	p_PaintTool;
	CMainWindow*    p_UI;

public:
	CGraphicLogic(CMsgObject* msgParent = NULL);
	virtual ~CGraphicLogic();

private:
	void initial();

public:
	void procMsg(const ts_msg& msg, bool isRemote);


};