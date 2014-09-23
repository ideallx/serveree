#include "CMsgSender.h"

CMsgSender::CMsgSender(void) :
	p_MsgReceiver(NULL) {
};

void CMsgSender::sendMessage(CMsgReceiver* p_recv, const ts_msg& msg, WPARAM wParam, LPARAM lParam, BOOL isremote) {
	if (!p_recv)
		return;

	p_recv->ProcessMessage(const_cast<ts_msg&>(msg), wParam, lParam, isremote);
};	

bool CMsgSender::addUpReceiver(CMsgReceiver* recv) {
	if (upperReceivers.count(recv) == 1)
		return false;

	upperReceivers.insert(recv);
	return true;
}

bool CMsgSender::addDownReceiver(CMsgReceiver* recv) {
	if (lowerReceivers.count(recv) == 1)
		return false;

	lowerReceivers.insert(recv);
	return true;
}

bool CMsgSender::removeUpperReceiver(CMsgReceiver* recv) {
	if (upperReceivers.count(recv) == 0)
		return false;

	upperReceivers.erase(recv);
	return true;
}

bool CMsgSender::removeLowerReceiver(CMsgReceiver* recv) {
	if (lowerReceivers.count(recv) == 0)
		return false;

	lowerReceivers.erase(recv);
	return true;
}

void CMsgSender::sendToUpLayer(const ts_msg& msg, WPARAM wParam, LPARAM lParam, 
	BOOL isRemote) {
	for (auto iter = upperReceivers.begin(); iter != upperReceivers.end(); iter++) {
		(*iter)->ProcessMessage(const_cast<ts_msg&>(msg), wParam, lParam, isRemote);
	}
}

void CMsgSender::sendToDownLayer(const ts_msg& msg, WPARAM wParam, LPARAM lParam, 
	BOOL isRemote) {
	for (auto iter = lowerReceivers.begin(); iter != lowerReceivers.end(); iter++) {
		(*iter)->ProcessMessage(const_cast<ts_msg&>(msg), wParam, lParam, isRemote);
	}
}