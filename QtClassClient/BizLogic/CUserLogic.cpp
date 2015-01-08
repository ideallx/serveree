#include "CUserLogic.h"

CUserLogic::CUserLogic(CMsgObject* msgParent) :
	CBaseLogic(msgParent),
	isLoggedIn(false),
    ub(NULL) {
}

CUserLogic::~CUserLogic() {


}

bool CUserLogic::procMsg(const ts_msg& msg, bool isRemote) {
    TS_MESSAGE_HEAD* head = (TS_MESSAGE_HEAD*) &msg;
    if (isRemote) {						// �ⲿ���ģ�Net���յ��ķ�������������
        switch (head->type) {
        case ENTERCLASS:
        case LEAVECLASS:
            {
                DOWN_AGENTSERVICE* down = (DOWN_AGENTSERVICE*) &msg;
                if (SuccessEnterClass == down->result)
                    isLoggedIn = true;
                else if (SuccessLeaveClass == down->result)
                    isLoggedIn = false;
            }
			break;
        case ENTERAGENT:
            {
                DOWN_AGENTSERVICE* down = (DOWN_AGENTSERVICE*) &msg;
                if (SuccessEnterClass == down->result)
                    isLoggedIn = true;
                else if (SuccessLeaveClass == down->result)
                    isLoggedIn = false;
            }
            break;
        case USERLIST:
            {
                SERVER_CLASS_USER_LIST* down = (SERVER_CLASS_USER_LIST*) &msg;
                for (int i = 0; i < down->userNumberInMessage; i++) {
                    ds->setUser(down->users[i].uid, down->users[i]);
                }
            }
            break;
        case REMOVEUSER:
            {
                SERVER_CLASS_REMOVE_USER* down = (SERVER_CLASS_REMOVE_USER*) &msg;
                ds->setLoggedInState(down->leaveUser, false);
            }
            break;
        case ADDUSER:
            {
                SERVER_CLASS_ADD_USER* down = (SERVER_CLASS_ADD_USER*) &msg;
                ds->setLoggedInState(down->enterUser.uid, true);
            }
            break;
		default:
			break;
        }
        sendToUp(const_cast<ts_msg&> (msg), 0, 0, true);
    } else {							// �ڲ����ģ�UI���յ�����Ϣ
        sendToDown(const_cast<ts_msg&> (msg), 0, 0, false);
    }
    return false;
}
