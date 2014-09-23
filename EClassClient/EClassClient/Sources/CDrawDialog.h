#pragma once

#include "../stdafx.h"
#include "CDisplayDialog.h"
#include "CCanvas.h"
#include <GdiPlus.h>
#include "CShapeCreator.h"
#include "CShapeContainer.h"

//#pragma comment(lib, "gdiplus.lib")		

using namespace Gdiplus;


class CDrawDialog : public CDisplayDialog {
private:
	bool isLeftPressed;
	enum ShapeType st;
	
	CShapeCreator* sc;

public:
	CDrawDialog(CMsgObject* msgParent, CWnd* pParent = NULL);	// 标准构造函数
	virtual ~CDrawDialog();

public:
	inline void setDrawType(enum ShapeType type) { st = type; }

	DECLARE_MESSAGE_MAP()
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};