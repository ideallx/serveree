#include "../stdafx.h"

#include "../../../EBoardServer/EBoardServer/DataUnit/CMessage.h"
#include "CShape.h"

class CShapeCreator {
private:
	DWORD curShapeID;
	DWORD curShapeType;
	DWORD curSeq;
	CPoint begin;

public:
	CShapeCreator();
	~CShapeCreator();

	void create(DWORD type, CPoint in);

	void generateGraphicsData(TS_GRAPHIC_PACKET& msg, CPoint p, bool isDone);
};