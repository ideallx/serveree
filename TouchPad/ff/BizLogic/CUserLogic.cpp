#include "CUserLogic.h"

CUserLogic::CUserLogic(CMsgObject* msgParent) :
	CBaseLogic(msgParent),
	isLoggedIn(false),
	ub(NULL),
	cn(NULL) {
}

CUserLogic::~CUserLogic() {


}

void CUserLogic::procMsg(const ts_msg& msg, bool isRemote) {
	if (NULL == cn)
		cn = static_cast<CClientNet*>(p_Parent->getAgent()->getModule("NET"));
	if (isRemote) {						// �ⲿ���ģ�Net���յ��ķ�������������
		DOWN_AGENTSERVICE* down = (DOWN_AGENTSERVICE*) &msg;

		switch (down->result) {
		case SuccessEnterClass:
			cn->addServerAddr(down->addr);
			isLoggedIn = true;
			break;
		case SuccessLeaveClass:
			cn->Stop();
			break;
		default:
			break;
		}
		return;
	} else {							// �ڲ����ģ�UI���յ�����Ϣ
		TS_MESSAGE_HEAD* head = (TS_MESSAGE_HEAD*) &msg;
		switch (head->type) {
		case ENTERCLASS:
			{
				

			}
		case ENTERAGENT:
			{

			}
		}
	}
}