#include "CShapeCreator.h"
#include "CShape.h"


CShapeCreator::CShapeCreator() :
	pt(NULL),
	curShapeID(0),
	curSeq(0),
	curShapeType(NONE) {
}

CShape* CShapeCreator::create(DWORD type, CPaintTools* in, CPoint p) {
	begin = p;
	curShapeType = type;
	pt = in;
	return CShapeFactory::CreateShape(curShapeID++, curShapeType, pt->m_penid, pt->m_brushid);
}

void CShapeCreator::generateGraphicsData(TS_GRAPHIC_PACKET& msg, CPoint p, bool isDone) {
	msg.data.Alpha = 1;
	msg.data.DoneFlag = isDone;
	msg.data.PageID = 0;
	msg.data.PointX = p.x;
	msg.data.PointY = p.y;
	msg.data.ShapeSeq = curSeq++;
	msg.data.ShapeID = curShapeID;
	msg.data.ShapeType = curShapeType;
	msg.data.BeginPx = begin.x;
	msg.data.BeginPy = begin.y;

	if (isDone)
		curShapeID++;

	msg.head.size = sizeof(TS_GRAPHIC_PACKET);
	msg.head.UID = SelfUID;	// TODO ≤‚ ‘”√
}