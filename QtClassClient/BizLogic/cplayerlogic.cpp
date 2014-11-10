#include "cplayerlogic.h"
#include "mainwindow.h"

CPlayerLogic::CPlayerLogic(CMsgObject* parent):
    CBaseLogic(parent) {
}

void CPlayerLogic::procRecvIsRemote(map<TS_UINT64, ts_msg> sendMap) {
    for (auto iter = sendMap.begin(); iter != sendMap.end(); iter++) {
        TS_PLAYER_PACKET *pmsg = (TS_PLAYER_PACKET*) &(iter->second);
        qDebug() << (char*)pmsg->filename;
        switch (pmsg->pa) {
        case ActionPrev:
        case ActionNext:
        case ActionStop:
            ui->signalPlayerMove(pmsg->pa);
            break;
        case ActionStart:
            ui->signalPlayerStart((char*) pmsg->filename);
            break;
        default:
            break;
        }
    }
}
