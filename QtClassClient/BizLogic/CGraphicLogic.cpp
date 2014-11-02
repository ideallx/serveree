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
