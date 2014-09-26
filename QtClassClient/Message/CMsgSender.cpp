#include "CMsgSender.h"

CMsgSender::CMsgSender(void) :
	p_MsgReceiver(NULL) {
};

void CMsgSender::sendMessage(CMsgReceiver* p_recv, const ts_msg& msg, WPARAM wParam, LPARAM lParam, BOOL isremote) {
	if (!p_recv)
		return;

	p_recv->ProcessMessage(const_cast<ts_msg&>(msg), wParam, lParam, isremote);
};	

bool CMsgSender::addReceiver(CMsgReceiver* recv) {
    if (receivers.count(recv) == 1)
		return false;

    receivers.insert(recv);
	return true;
}

bool CMsgSender::removeReceiver(CMsgReceiver* recv) {
    if (receivers.count(recv) == 0)
		return false;

    receivers.erase(recv);
	return true;
}

void CMsgSender::sendToAll(const ts_msg& msg, WPARAM wParam, LPARAM lParam,
	BOOL isRemote) {
    for (auto iter = receivers.begin(); iter != receivers.end(); iter++) {
		(*iter)->ProcessMessage(const_cast<ts_msg&>(msg), wParam, lParam, isRemote);
	}
}
