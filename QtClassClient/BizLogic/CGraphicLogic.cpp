#include <QDebug>
#include "CGraphicLogic.h"
#include "../LayerUI/mainwindow.h"
#include "../Net/CClientNet.h"


CGraphicLogic::CGraphicLogic(CMsgObject *parent) :
    CBaseLogic(parent) {
}

void CGraphicLogic::procIsRemote(const ts_msg& msg) {
    TS_GRAPHIC_PACKET* gmsg = (TS_GRAPHIC_PACKET*) &msg;
    if (gmsg->SceneID == globalUID) {
        gmsg->SceneID = SelfUID;
    } else if (gmsg->SceneID == SelfUID) {
        gmsg->SceneID = gmsg->head.UID;
    }
}


void CGraphicLogic::procRecvIsRemote(map<TS_UINT64, ts_msg> sendMap) {
    for (auto i = sendMap.begin(); i != sendMap.end(); i++) {
        ui->ProcessMessage(i->second, 0, 0, true);
    }
}
