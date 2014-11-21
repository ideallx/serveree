#include "CUserLogic.h"
#include "../LayerUI/mainwindow.h"

CUserLogic::CUserLogic(CMsgObject* msgParent) :
	CBaseLogic(msgParent),
	isLoggedIn(false),
    ub(NULL) {
}

CUserLogic::~CUserLogic() {


}

bool CUserLogic::procMsg(const ts_msg& msg, bool isRemote) {
    TS_MESSAGE_HEAD* head = (TS_MESSAGE_HEAD*) &msg;
    if (isRemote) {						// 外部来的，Net层收到的服务器来的下行
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
		default:
			break;
        }
        sendToUp(const_cast<ts_msg&> (msg), 0, 0, true);
    } else {							// 内部来的，UI层收到的信息
		switch (head->type) {
		case ENTERCLASS:
        {
            UP_AGENTSERVICE* up = (UP_AGENTSERVICE*) &msg;
            up->classid = 10000;
            up->head.sequence = 0;
            break;
        }
		case LEAVECLASS:
        {
            UP_AGENTSERVICE* up = (UP_AGENTSERVICE*) &msg;
            up->classid = 10000;
            up->head.sequence = 0;
            break;
        }
		default:
			break;
		}
        sendToDown(const_cast<ts_msg&> (msg), 0, 0, false);
    }
    return false;
}
