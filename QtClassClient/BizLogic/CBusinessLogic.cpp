#include "CBusinessLogic.h"

CBusinessLogic::CBusinessLogic(CMsgObject* parent) :
	CMsgObject(parent),
    m_UserLogic(new CUserLogic(this)) {
}

CBusinessLogic::~CBusinessLogic() {
    delete m_UserLogic;
}

void CBusinessLogic::ProcessMessage(ts_msg& msg, WPARAM wParam, LPARAM lParam, BOOL isremote) {
	TS_MESSAGE_HEAD* head = (TS_MESSAGE_HEAD*) &msg;
	if (isremote) {							// �ⲿ�������Ǿ��Ǵ�Net������
		if (head->type > PACKETCONTROL) {	// Net�㴫���Ŀ��������д���
			m_UserLogic->procMsg(msg, true);
		} else {							// Net�㴫��������ָ���UI��
			// TODO
			sendToUpLayer(msg, wParam, lParam, true);
		}
	} else {								// �ڲ���������UI������
		if (head->type > PACKETCONTROL) {	
			m_UserLogic->procMsg(msg, false);
		} else {
            switch (head->type) {
			default:
				break;
			}
			sendToDownLayer(msg, wParam, lParam, false);
		}
	}
}
