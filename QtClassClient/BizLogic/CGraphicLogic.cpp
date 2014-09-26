#include <QDebug>
#include "CGraphicLogic.h"
#include "mainwindow.h"
#include "../Net/CClientNet.h"

CGraphicLogic::CGraphicLogic(CMsgObject *parent) :
    CBaseLogic(parent) {
}

bool CGraphicLogic::procMsg(const ts_msg& msg, bool isRemote) {
    MainWindow* ui = static_cast<MainWindow*>(p_Parent->getAgent()->getModule("UI"));
    CClientNet* cn = static_cast<CClientNet*>(p_Parent->getAgent()->getModule("NET"));

    if (!isRemote) {
        cn->ProcessMessage(const_cast<ts_msg&> (msg), 0, 0, isRemote);
        return false;
    }
    TS_GRAPHIC_PACKET* gmsg = (TS_GRAPHIC_PACKET*) &msg;
    TS_UINT64 uid = gmsg->head.UID;

    struct lastState s;
    if (!last.contains(uid)) {
        s.graphicSeq = 0;
        s.shapeID = 0;
        last.insert(uid, s);
    } else {
        s = last[uid];
    }

	s.point = QPointF(gmsg->data.PointX, gmsg->data.PointY);

    if (gmsg->data.ShapeSeq >= s.graphicSeq && s.shapeID == gmsg->data.ShapeID) { // common condition
        s.graphicSeq = gmsg->data.ShapeSeq;
        ui->ProcessMessage(const_cast<ts_msg&> (msg), 0, 0, isRemote);
    } else if (gmsg->data.ShapeID > s.shapeID) {
        s.shapeID = gmsg->data.ShapeID;
		s.graphicSeq = gmsg->data.ShapeSeq;
        ui->ProcessMessage(const_cast<ts_msg&> (msg), 1, 0, isRemote);
    }
    last[uid] = s;
    return false;
}
