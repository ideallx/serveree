#include "cauthlogic.h"
#include "../LayerUI/mainwindow.h"

CAuthLogic::CAuthLogic(CMsgObject* parent):
    CBaseLogic(parent) {
}

void CAuthLogic::procRecvIsRemote(map<TS_UINT64, ts_msg> sendMap) {
    for (auto i = sendMap.begin(); i != sendMap.end(); i++) {
        SET_USER_WRITE_AUTH* down = (SET_USER_WRITE_AUTH*) &(i->second);
        ui->setWriteable(down->toUID, down->sceneID, down->writeable);
    }
}
