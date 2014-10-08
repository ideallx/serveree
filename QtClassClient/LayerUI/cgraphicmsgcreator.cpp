#include "cgraphicmsgcreator.h"

CGraphicMsgCreator::CGraphicMsgCreator() :
    curShapeID(0),
    curSeq(1),
    curShapeType(NONE),
    curPenBrushid(0) {
}

void CGraphicMsgCreator::create(DWORD type, QPointF p) {
    begin = p;
    curShapeType = type;
}

void CGraphicMsgCreator::generateGraphicsData(TS_GRAPHIC_PACKET& msg, QPointF p, bool isDone) {
    if (isDone) {
        msg.graphicsType = GraphicPacketEndMove;
    } else {
        msg.graphicsType = GraphicPacketNormal;
    }

    msg.head.size = sizeof(TS_GRAPHIC_PACKET);
    msg.head.UID = SelfUID;
    msg.head.type = GRAPHICS;
    msg.head.subSeq = curSeq++;

    msg.data.Alpha = 1;
    msg.data.DoneFlag = isDone;
    msg.data.PageID = 0;
    msg.data.PointX = p.x();
    msg.data.PointY = p.y();
    msg.data.ShapeID = curShapeID;
    msg.data.ShapeType = curShapeType;
    msg.data.BeginPx = begin.x();
    msg.data.BeginPy = begin.y();
}

void CGraphicMsgCreator::generatePenBrushData(TS_GRAPHIC_PACKET& msg, QPen& p, QBrush& b) {
    curPenBrushid++;
    msg.graphicsType = GraphicPacketPenBrush;

    msg.head.size = sizeof(TS_GRAPHIC_PACKET);
    msg.head.UID = SelfUID;
    msg.head.type = GRAPHICS;
    msg.head.subSeq = curSeq++;

    msg.penbrush.brushB = b.color().blue();
    msg.penbrush.brushG = b.color().green();
    msg.penbrush.brushR = b.color().red();
    msg.penbrush.brushid = curPenBrushid;

    msg.penbrush.penR = p.color().red();
    msg.penbrush.penG = p.color().green();
    msg.penbrush.penB = p.color().blue();
    msg.penbrush.penWidth = p.width();
    msg.penbrush.penid = curPenBrushid;
}

void CGraphicMsgCreator::generateClearScreen(TS_GRAPHIC_PACKET& msg) {
    msg.graphicsType = GraphicPacketCls;

    msg.head.size = sizeof(TS_GRAPHIC_PACKET);
    msg.head.UID = SelfUID;
    msg.head.type = GRAPHICS;
    msg.head.subSeq = curSeq++;
}
