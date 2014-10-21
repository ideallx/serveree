#include "CBusinessLogic.h"

CBusinessLogic::CBusinessLogic(CMsgObject* parent) :
	CMsgObject(parent),
    m_UserLogic(new CUserLogic(this)),
    m_GraphicLogic(new CGraphicLogic(this)){
}

CBusinessLogic::~CBusinessLogic() {
    delete m_UserLogic;
}

void CBusinessLogic::ProcessMessage(ts_msg& msg, WPARAM wParam, LPARAM lParam, BOOL isremote) {
    TS_MESSAGE_HEAD* head = (TS_MESSAGE_HEAD*) &msg;
    if (head->type > PACKETCONTROL) {	// Net�㴫���Ŀ��������д���
        m_UserLogic->procMsg(msg, isremote);
    } else {							// Net�㴫��������ָ���UI��
        if (!m_UserLogic->isServerAvailable() && !isremote)
            return;

        switch (head->type) {
        case GRAPHICS:
            m_GraphicLogic->procMsg(msg, isremote);
            break;
        default:
            break;
            // sendToAll(msg, wParam, lParam, isremote);
        }
    }
}
