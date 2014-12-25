#include "cauthlogic.h"
#include "../LayerUI/mainwindow.h"

CAuthLogic::CAuthLogic(CMsgObject* parent):
    CBaseLogic(parent) {
}

bool CAuthLogic::procMsg(const ts_msg& msg, bool isRemote) {
    if (isRemote) {						// �ⲿ���ģ�Net���յ��ķ�������������
        SET_USER_WRITE_AUTH* down = (SET_USER_WRITE_AUTH*) &msg;
        ds->setWriteable(down->toUID, down->writeable);
        sendToUp(msg, 0, 0, true);
    } else {							// �ڲ����ģ�UI���յ�����Ϣ
        sendToDown(msg, 0, 0, false);
    }
    return false;
}
