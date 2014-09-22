#pragma once

#include "../stdafx.h"
#include <gdiPlus.h>
#include <vector>
#include <map>
//#pragma comment(lib, "gdiplus.lib")		

using namespace Gdiplus;
using namespace std;

// Ӧ�ò�ȫ�ֵ�Pen����Ĺ���Ա
class CPaintTools
{
private:
	Pen*			m_pPen;									// default pen 
	Brush*			m_pBrush;								// default brush;

public:
	DWORD			m_penid;									// latest pen id
	DWORD			m_brushid;								// latest brush id

private:
	map<DWORD, Pen*>				m_PenManager;			// �洢�͹���Graphics Pen
	map<DWORD, Brush*>				m_BrushManager;			// �洢�͹���Graphics Brush

public:
	CPaintTools(void);
	virtual ~CPaintTools(void);
	void initialize(void);

public:
	BOOL addPen(DWORD id, Pen* pen);						// ���һ��Pen
	BOOL deletePen(DWORD id);								// ɾ��Pen
	Pen* getPen(DWORD id);									// ͨ��Pen ID �����ҿ�
	inline Pen* getLatestPen() { return getPen(m_penid); }
	
public:
	BOOL addBrush(DWORD id, Brush* brush);					// ���һ��Brush
	BOOL deleteBrush(DWORD id);								// ɾ��Brush
	Brush* getBrush(DWORD id);								// ͨ��Brush ID �����ҿ�
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
	// �û��ڲ����Ĺ��̻�ı�Pen
	// ÿһ�θı䶼�ر���¼�������Ҹ����µ�Pen ID
	// ��Pen ID���������ݰ����㲥�����е��û�
	// Pen ID ��Ӧ�ò�Ψһ��ID�����������κ�shape 
	// ����Shape Page
	unsigned int		m_PenID;							// Shape ��ʹ�õ�Pen��ID, ��ǰ��״ʹ�ø�Pen������ͼ�� 
	unsigned int		m_BrushID;
	DWORD				m_MaxSeq;							// �������

protected:													// for other Shape;
	Point				m_StartPoint;
	Point				m_EndPoint;
	Rect				m_Rect;								// Outer rect contains the shape

protected:
	DWORD				m_ShapeType;						// enum shape type
	map<DWORD, Point*>	m_PointList;						// ���ڴ洢����ͼ�εĵ���

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
	BOOL addPoint(DWORD seq, Point* b, Point* p);						// �������ͼ�εĵ�λ
	void clear(void);

public:
	// Draw the shape by a certain offset on X or Y axis
	// ��ʵ�ʵ�ͼ�λ����У���״�п��ܰ���һ����ƫ���������ƣ������ǻ����ڼȶ���
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
		//g->SetSmoothingMode(SmoothingModeAntiAlias);				// �����
		
		if (m_PointList.size()>=2){									// �㹻�ĵ���
			GraphicsPath* path = new GraphicsPath();

			auto iter = m_PointList.begin();
			for (unsigned int i=0;i<m_PointList.size()-1;i++){		// i���㣬i-1���߶�
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
