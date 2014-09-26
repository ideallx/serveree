#include "cgraphicmsgcreator.h"

CGraphicMsgCreator::CGraphicMsgCreator() :
    curShapeID(0),
    curSeq(1),
    curShapeType(NONE) {
}

void CGraphicMsgCreator::create(DWORD type, QPointF p) {
    begin = p;
    curShapeType = type;
}

void CGraphicMsgCreator::generateGraphicsData(TS_GRAPHIC_PACKET& msg, QPointF p, bool isBegin) {
    if (isBegin) {
        curShapeID++;
    }
    msg.data.Alpha = 1;
    msg.data.BeginFlag = isBegin;
    msg.data.PageID = 0;
    msg.data.PointX = p.x();
    msg.data.PointY = p.y();
    msg.data.ShapeSeq = curSeq++;
    msg.data.ShapeID = curShapeID;
    msg.data.ShapeType = curShapeType;
    msg.data.BeginPx = begin.x();
    msg.data.BeginPy = begin.y();

    msg.head.size = sizeof(TS_GRAPHIC_PACKET);
    msg.head.UID = SelfUID;
    msg.head.type = GRAPHICS;
}
