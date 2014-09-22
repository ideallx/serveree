#pragma once
#include "../stdafx.h"
#include "CShape.h"
#include <map>
#include <iop_thread.h>
#include "../../../EBoardServer/EBoardServer/DataUnit/CMessage.h"

using namespace std;
/************************** Shape Stage*******************************/
/******************* 图形进入图形容器前的缓冲区 ************/
class CShapeStage											// 图形登台区
{
private:
	map<DWORD, CShape*>	m_ShapeStage;
	iop_lock_t			m_Lock;

public:
	CShapeStage(void);
	virtual ~CShapeStage(void);

public:
	CShape* FindShape(DWORD uid);
	void MapShape(DWORD, CShape* ps);				// in stage area, a new shape would map an id;
	void Clear(void);

public:
	void Draw(Graphics* pgc, CPaintTools* pt, int offset_X, int offset_Y);
};

/*******************************存储所有图形的容器************************************/
class CShapePage:											// 图形容器 -- 页
	public CShapeFactory
{
private:
	vector<CShape*>			m_ShapePage;					// vector<T>类型的向量列表对象
	CShapeStage				m_ShapeStage;					// 该页登台区
	int						MaxSize;						// vector的容量。
	iop_lock_t				m_Lock;
	Point					m_beginPoint;

public:
	CShapePage(void);
	virtual ~CShapePage(void);

public:
	inline void setBeginPoint(Point p) { m_beginPoint = p; }

	int Size(void);
    void AddShape(CShape* pShape);							// 添加图形
	void UpdateShape(CShape* pShape);						// 更新图形
	CShape* GetShape(unsigned int i);						// 获得在位置i的图形
	void Clear(void);
	CShape* FindShape(DWORD id);							// 获得Shape ID为id的图形
	
public:
	CShape* MakeShape(const TS_GRAPHIC_PACKET& gPacket, CPaintTools* pt);	// 构建图形
	void Draw(Graphics* pgc, CPaintTools* pt, int offset_X, int offset_Y);
	void DrawCurrent(Graphics* pgc, CPaintTools* pt, int offset_X, int offset_Y);	// 绘制正在绘制的图形
};

