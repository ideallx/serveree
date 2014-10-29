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
    CClientNet* cn = static_cast<CClientNet*>(p_Parent->getAgent()->getModule("NET"));
    MainWindow* ui = static_cast<MainWindow*>(p_Parent->getAgent()->getModule("UI"));

    TS_MESSAGE_HEAD* head = (TS_MESSAGE_HEAD*) &msg;
    if (isRemote) {						// 外部来的，Net层收到的服务器来的下行
        switch (head->type) {
        case ENTERCLASS:
        case LEAVECLASS:
        {
            DOWN_AGENTSERVICE* down = (DOWN_AGENTSERVICE*) &msg;
            ui->sendPrompt(down->result);

            switch (down->result) {
            case SuccessEnterClass:
                cn->addServerAddr(down->addr);
                cn->setTimeDiff(down->head.time - getServerTime());
                cn->startupHeartBeat();
                cn->setUID(down->uid);
                ui->enterClassResult(true);
                ui->setRole(down->role);
                isLoggedIn = true;
                break;
            case SuccessLeaveClass:
                ui->leaveClassResult(true);
                isLoggedIn = false;
                //cn->Stop();
                break;
            default:
                break;
            }
            break;
        }
        case ADDUSER:
        {
            SERVER_CLASS_ADD_USER* down = (SERVER_CLASS_ADD_USER*) &msg;
            ui->addUser(down->enterUser.uid, (char *) down->enterUser.username);
            break;
        }
        case USERLIST:
        {
            SERVER_CLASS_USER_LIST* down = (SERVER_CLASS_USER_LIST*) &msg;
            for (int i = 0; i < down->userNumberInMessage; i++) {
                ui->addUser(down->users[i].uid, (char *) down->users[i].username);
            }
            break;
        }
        case REMOVEUSER:
        {
            SERVER_CLASS_REMOVE_USER* down = (SERVER_CLASS_REMOVE_USER*) &msg;
            ui->removeUser(down->leaveUser);
            break;
        }
        default:
            break;
        }
    } else {							// 内部来的，UI层收到的信息
		switch (head->type) {
		case ENTERCLASS:
			{
                UP_AGENTSERVICE* up = (UP_AGENTSERVICE*) &msg;
                up->classid = 10000;
                up->head.sequence = 0;

                cn->ProcessMessage(const_cast<ts_msg&> (msg), 0, 0, false);
				break;
			}
		case LEAVECLASS:
			{
                UP_AGENTSERVICE* up = (UP_AGENTSERVICE*) &msg;
                up->classid = 10000;
                up->head.sequence = 0;

                cn->ProcessMessage(const_cast<ts_msg&> (msg), 0, 0, false);
				break;
            }
		default:
			break;
		}
    }
    return false;
}
