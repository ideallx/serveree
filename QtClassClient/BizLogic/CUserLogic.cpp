#include "CUserLogic.h"

CUserLogic::CUserLogic(CMsgObject* msgParent) :
	CBaseLogic(msgParent),
	isLoggedIn(false),
    ub(NULL) {
}

CUserLogic::~CUserLogic() {


}

bool CUserLogic::procMsg(const ts_msg& msg, bool isRemote) {
    CClientNet* cn = static_cast<CClientNet*>(p_Parent->getAgent()->getModule("NET"));

	if (isRemote) {						// �ⲿ���ģ�Net���յ��ķ�������������
		DOWN_AGENTSERVICE* down = (DOWN_AGENTSERVICE*) &msg;

		switch (down->result) {
		case SuccessEnterClass:
			cn->addServerAddr(down->addr);
			isLoggedIn = true;
			break;
		case SuccessLeaveClass:
            isLoggedIn = false;
			//cn->Stop();
			break;
		default:
			break;
        }
    } else {							// �ڲ����ģ�UI���յ�����Ϣ
		TS_MESSAGE_HEAD* head = (TS_MESSAGE_HEAD*) &msg;
		switch (head->type) {
		case ENTERCLASS:
			{
                UP_AGENTSERVICE* up = (UP_AGENTSERVICE*) &msg;
                up->classid = 10000;
                up->role = RoleTeacher;
                up->head.sequence = 0;

                memcpy(up->password, "abcdef", 20);
                memcpy(up->username, "abcdef", 20);
                cn->ProcessMessage(const_cast<ts_msg&> (msg), 0, 0, false);
			}
		case LEAVECLASS:
			{
                UP_AGENTSERVICE* up = (UP_AGENTSERVICE*) &msg;
                up->classid = 10000;
                up->role = RoleTeacher;
                up->head.sequence = 0;

                memcpy(up->password, "abcdef", 20);
                memcpy(up->username, "abcdef", 20);
                cn->ProcessMessage(const_cast<ts_msg&> (msg), 0, 0, false);
			}
		}
	}
    return false;
}
