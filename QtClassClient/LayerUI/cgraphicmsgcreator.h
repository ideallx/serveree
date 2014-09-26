#ifndef CGRAPHICMSGCREATOR_H
#define CGRAPHICMSGCREATOR_H

#include <QPointF>
#include "../stdafx.h"
#include "../Reliable/DataUnit/CMessage.h"

class CGraphicMsgCreator
{
public:
    CGraphicMsgCreator();
    ~CGraphicMsgCreator();

    DWORD curShapeID;
    DWORD curShapeType;
    DWORD curSeq;
    QPointF begin;

    void create(DWORD type, QPointF in);

    void generateGraphicsData(TS_GRAPHIC_PACKET& msg, QPointF p, bool isBegin);
};

#endif // CGRAPHICMSGCREATOR_H
