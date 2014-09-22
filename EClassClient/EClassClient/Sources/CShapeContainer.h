#pragma once
#include "../stdafx.h"
#include "CShape.h"
#include <map>
#include <iop_thread.h>
#include "../../../EBoardServer/EBoardServer/DataUnit/CMessage.h"

using namespace std;
/************************** Shape Stage*******************************/
/******************* ͼ�ν���ͼ������ǰ�Ļ����� ************/
class CShapeStage											// ͼ�ε�̨��
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

/*******************************�洢����ͼ�ε�����************************************/
class CShapePage:											// ͼ������ -- ҳ
	public CShapeFactory
{
private:
	vector<CShape*>			m_ShapePage;					// vector<T>���͵������б����
	CShapeStage				m_ShapeStage;					// ��ҳ��̨��
	int						MaxSize;						// vector��������
	iop_lock_t				m_Lock;
	Point					m_beginPoint;

public:
	CShapePage(void);
	virtual ~CShapePage(void);

public:
	inline void setBeginPoint(Point p) { m_beginPoint = p; }

	int Size(void);
    void AddShape(CShape* pShape);							// ���ͼ��
	void UpdateShape(CShape* pShape);						// ����ͼ��
	CShape* GetShape(unsigned int i);						// �����λ��i��ͼ��
	void Clear(void);
	CShape* FindShape(DWORD id);							// ���Shape IDΪid��ͼ��
	
public:
	CShape* MakeShape(const TS_GRAPHIC_PACKET& gPacket, CPaintTools* pt);	// ����ͼ��
	void Draw(Graphics* pgc, CPaintTools* pt, int offset_X, int offset_Y);
	void DrawCurrent(Graphics* pgc, CPaintTools* pt, int offset_X, int offset_Y);	// �������ڻ��Ƶ�ͼ��
};

