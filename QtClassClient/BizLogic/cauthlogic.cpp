#include "cauthlogic.h"
#include "../LayerUI/mainwindow.h"

CAuthLogic::CAuthLogic(CMsgObject* parent):
    CBaseLogic(parent) {
}

bool CAuthLogic::procMsg(const ts_msg& msg, bool isRemote) {
    if (isRemote) {						// 外部来的，Net层收到的服务器来的下行
        SET_USER_WRITE_AUTH* down = (SET_USER_WRITE_AUTH*) &msg;
        ds->setWriteable(down->toUID, down->writeable);
        sendToUp(msg, 0, 0, true);
    } else {							// 内部来的，UI层收到的信息
        sendToDown(msg, 0, 0, false);
    }
    return false;
}
