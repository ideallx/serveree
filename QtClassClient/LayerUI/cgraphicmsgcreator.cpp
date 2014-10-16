#include "cgraphicmsgcreator.h"

CGraphicMsgCreator::CGraphicMsgCreator(DWORD sceneID) :
    curShapeID(0),
    curSeq(1),
    curShapeType(NONE),
    curPenBrushid(0),
    sceneID(sceneID) {
}

void CGraphicMsgCreator::create(DWORD type, QPointF p) {
    begin = p;
    curShapeType = type;
}

void CGraphicMsgCreator::buildCommonInfo(TS_GRAPHIC_PACKET& msg) {
    msg.SceneID = sceneID;
    msg.head.size = sizeof(TS_GRAPHIC_PACKET);
    msg.head.UID = SelfUID;
    msg.head.type = GRAPHICS;
    msg.head.subSeq = curSeq++;

}

void CGraphicMsgCreator::generateGraphicsData(TS_GRAPHIC_PACKET& msg, QPointF p, bool isDone) {
    if (isDone) {
        msg.graphicsType = GraphicPacketEndMove;
    } else {
        msg.graphicsType = GraphicPacketNormal;
    }
    buildCommonInfo(msg);

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

void CGraphicMsgCreator::generateEraserData(TS_GRAPHIC_PACKET& msg, QPointF p) {
    msg.graphicsType = GraphicPacketEraser;
    buildCommonInfo(msg);

    msg.data.Alpha = 1;
    msg.data.DoneFlag = true;
    msg.data.PointX = p.x();
    msg.data.PointY = p.y();
}

void CGraphicMsgCreator::generateScreenMove(TS_GRAPHIC_PACKET& msg, QPoint p) {
    msg.graphicsType = GraphicPacketMoveScreen;
    buildCommonInfo(msg);

    msg.data.DoneFlag = true;
    msg.data.PointX = p.x();
    msg.data.PointY = p.y();
}

void CGraphicMsgCreator::generatePenBrushData(TS_GRAPHIC_PACKET& msg, QPen& p, QBrush& b) {
    msg.graphicsType = GraphicPacketPenBrush;
    buildCommonInfo(msg);

    curPenBrushid++;
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
    buildCommonInfo(msg);
}
