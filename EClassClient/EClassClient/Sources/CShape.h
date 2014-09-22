#pragma once

#include "../stdafx.h"
#include <gdiPlus.h>
#include <vector>
#include <map>
//#pragma comment(lib, "gdiplus.lib")		

using namespace Gdiplus;
using namespace std;

// 应用层全局的Pen对象的管理员
class CPaintTools
{
private:
	Pen*			m_pPen;									// default pen 
	Brush*			m_pBrush;								// default brush;

public:
	DWORD			m_penid;									// latest pen id
	DWORD			m_brushid;								// latest brush id

private:
	map<DWORD, Pen*>				m_PenManager;			// 存储和管理Graphics Pen
	map<DWORD, Brush*>				m_BrushManager;			// 存储和管理Graphics Brush

public:
	CPaintTools(void);
	virtual ~CPaintTools(void);
	void initialize(void);

public:
	BOOL addPen(DWORD id, Pen* pen);						// 添加一个Pen
	BOOL deletePen(DWORD id);								// 删除Pen
	Pen* getPen(DWORD id);									// 通过Pen ID 来查找控
	inline Pen* getLatestPen() { return getPen(m_penid); }
	
public:
	BOOL addBrush(DWORD id, Brush* brush);					// 添加一个Brush
	BOOL deleteBrush(DWORD id);								// 删除Brush
	Brush* getBrush(DWORD id);								// 通过Brush ID 来查找控
	inline Brush* getLatestBrush() { return getBrush(m_brushid); }

public:
	void clear(void);
};


/**********************************************************/

enum ShapeType {
	NONE, 
	SCRIPTS, 
	LINE, 
	RECTANGLE, 
	ELLIPSE, 
	ROUNDRECT, 
	TRIANGLE, 
	IMAGE,
};

class CShape
{
private: 
	unsigned int		m_ID;								// Shape ID
	// 用户在操作的过程会改变Pen
	// 每一次改变都回被记录下来并且赋予新的Pen ID
	// 该Pen ID会随着数据包被广播至所有的用户
	// Pen ID 是应用层唯一的ID，不依赖于任何shape 
	// 或者Shape Page
	unsigned int		m_PenID;							// Shape 所使用的Pen的ID, 当前形状使用该Pen来绘制图形 
	unsigned int		m_BrushID;
	DWORD				m_MaxSeq;							// 最大的序号

protected:													// for other Shape;
	Point				m_StartPoint;
	Point				m_EndPoint;
	Rect				m_Rect;								// Outer rect contains the shape

protected:
	DWORD				m_ShapeType;						// enum shape type
	map<DWORD, Point*>	m_PointList;						// 用于存储定义图形的点阵

public:
	CShape(void);
	virtual ~CShape(void){
		clear();
	};

public:
	inline DWORD getType(void) { return m_ShapeType; }
	inline unsigned int getID(void) { return m_ID; }
	inline unsigned int getPenID(void) { return m_PenID; }
	inline unsigned int getBrushID(void) { return m_BrushID; }
	void setProperties(DWORD id, DWORD type, DWORD penid, DWORD brushid);

public:
	BOOL addPoint(DWORD seq, Point* b, Point* p);						// 添加描述图形的点位
	void clear(void);

public:
	// Draw the shape by a certain offset on X or Y axis
	// 在实际的图形绘制中，形状有可能按照一定的偏移量来绘制，而不是绘制在既定的
	// 
	virtual void Draw(Graphics* g, Pen* p, int offset_X, int offset_Y) {;}
};

class CLine:
	public CShape
{
public:
	virtual void Draw(Graphics* g, Pen* p, int offset_X, int offset_Y){
		g->DrawLine(p, m_StartPoint.X + offset_X, m_StartPoint.Y + offset_Y, 
								m_EndPoint.X + offset_X, m_EndPoint.Y + offset_Y);
	};
};

class CScripts:
	public CShape
{
public:
	virtual void Draw(Graphics* g, Pen* p, int offset_X, int offset_Y){
		Point *p1, *p2;
		//g->SetSmoothingMode(SmoothingModeAntiAlias);				// 抗锯齿
		
		if (m_PointList.size()>=2){									// 足够的点数
			GraphicsPath* path = new GraphicsPath();

			auto iter = m_PointList.begin();
			for (unsigned int i=0;i<m_PointList.size()-1;i++){		// i个点，i-1个线段
				p1 = iter++->second;
				p2 = iter->second;
				path->AddLine(p1->X + offset_X, p1->Y + offset_Y, p2->X + offset_X, p2->Y + offset_Y);
			}

			g->DrawPath(p, path);
		}
	};
};

class CRectShape:
	public CShape
{
public:
	virtual void Draw(Graphics* g, Pen* p, int offset_X, int offset_Y){
		g->DrawRectangle(p, m_Rect.X+offset_X, m_Rect.Y+offset_Y, m_Rect.Width, m_Rect.Height);
	};
};

class CRoundRect:
	public CShape
{
public:
	virtual void Draw(Graphics* g, Pen* p, int offset_X, int offset_Y){
		
	};
};

class CEllipse:
	public CShape
{
public:
	virtual void Draw(Graphics* g, Pen* p, int offset_X, int offset_Y){
		g->DrawEllipse(p, m_Rect.X+offset_X, m_Rect.Y+offset_Y, m_Rect.Width, m_Rect.Height);
	};
};

class CTriangle:
	public CShape
{
public:
	virtual void Draw(Graphics* g, Pen* p, int offset_X, int offset_Y){
		// wait for implementation
	};
};

class CImageShape:
	public CShape
{
private: 
	Image* pimg;

public:
	CImageShape(void){pimg = NULL;};
	virtual ~CImageShape(void){};

public:
	void SetImage(Image* img){
		pimg = img;
	};

public:
	virtual void Draw(Graphics* g, Pen* p, int offset_X, int offset_Y){
		g->DrawImage(pimg, m_Rect.X + offset_X, m_Rect.Y + offset_Y, m_Rect.Width, m_Rect.Height);
	};
};


/******************************ShapeFactory********************************/
class CShapeFactory
{
public:
	CShapeFactory(void){};
	virtual ~CShapeFactory(void){};

public:
	static CShape* CreateShape(DWORD id, DWORD type, DWORD penid, DWORD brushid){
		CShape* ps = NULL;
		switch(type)
		{
		case LINE:
			ps = new CLine;
			break;
		case RECTANGLE:
			ps = new CRectShape;
			break;
		case SCRIPTS:
			ps = new CScripts;
			break;
		case ROUNDRECT:
			ps = new CRoundRect;
			break;
		case TRIANGLE:
			ps = new CTriangle;
			break;
		case ELLIPSE:
			ps = new CEllipse;
			break;
		default:
			break;
		}

		if (ps) ps->setProperties(id, type, penid, brushid);
		return ps;
	};
};
