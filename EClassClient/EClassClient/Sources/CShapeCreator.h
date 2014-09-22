#include "../stdafx.h"

#include "../../../EBoardServer/EBoardServer/DataUnit/CMessage.h"
#include "CShape.h"

class CShapeCreator {
private:
	CPaintTools* pt;
	DWORD curShapeID;
	DWORD curShapeType;
	DWORD curSeq;
	CPoint begin;

public:
	CShapeCreator();
	~CShapeCreator();

	CShape* create(DWORD type, CPaintTools* pt, CPoint in);
	inline void setPaintTool(CPaintTools* in) { pt = in; }

	void generateGraphicsData(TS_GRAPHIC_PACKET& msg, CPoint p, bool isDone);
};