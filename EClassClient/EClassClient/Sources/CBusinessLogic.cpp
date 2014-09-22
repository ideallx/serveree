#include "CBusinessLogic.h"
#include "CShape.h"
#include "CShapeContainer.h"


CBusinessLogic::CBusinessLogic(CMsgObject* parent) :
	CMsgObject(parent) {
	ul = new CUserLogic(this);
}

CBusinessLogic::~CBusinessLogic() {
	delete ul;
}

void CBusinessLogic::ProcessMessage(ts_msg& msg, WPARAM wParam, LPARAM lParam, BOOL isremote) {
	TS_MESSAGE_HEAD* head = (TS_MESSAGE_HEAD*) &msg;
	if (head->type > PACKETCONTROL) {
		ul->procMsg(msg);
	} else {
		sendToLower(msg, wParam, lParam, false);
	}
}