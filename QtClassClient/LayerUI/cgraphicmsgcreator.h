#ifndef CGRAPHICMSGCREATOR_H
#define CGRAPHICMSGCREATOR_H

#include <QPointF>
#include <QPen>
#include <QBrush>
#include "../stdafx.h"
#include "../Reliable/DataUnit/CMessage.h"

class CGraphicMsgCreator
{
public:
    CGraphicMsgCreator(DWORD sceneID);
    ~CGraphicMsgCreator();

    DWORD curShapeID;
    DWORD curShapeType;
    DWORD curSeq;
    QPointF begin;
    DWORD sceneID;

    DWORD curPenBrushid;

    void create(DWORD type, QPointF in);

    void generateGraphicsData(TS_GRAPHIC_PACKET& msg, QPointF p, bool isDone);

    void generatePenBrushData(TS_GRAPHIC_PACKET& msg, QPen& p, QBrush& b);

    void generateClearScreen(TS_GRAPHIC_PACKET& msg);
};

#endif // CGRAPHICMSGCREATOR_H
