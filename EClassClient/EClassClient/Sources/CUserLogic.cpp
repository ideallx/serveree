#include "CUserLogic.h"
#include "CClientNet.h"

CUserLogic::CUserLogic(CMsgObject* msgParent) :
	CBaseLogic(msgParent) {

}

CUserLogic::~CUserLogic() {


}

void CUserLogic::procMsg(const ts_msg& msg) {
	CClientNet* cn = static_cast<CClientNet*>(msgParent->getAgent()->getModule("NET"));
	DOWN_AGENTSERVICE* down = (DOWN_AGENTSERVICE*) &msg;

	switch (down->result) {
	case SuccessEnterClass:
		cn->addServerAddr(down->addr);
		break;
	case SuccessLeaveClass:
		cn->Stop();
		break;
	default:
		break;
	}
	return;
}