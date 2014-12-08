#include "CMsgSender.h"

CMsgSender::CMsgSender(void) :
	p_MsgReceiver(NULL) {
}

void CMsgSender::sendMessage(CMsgReceiver* p_recv, const ts_msg& msg, WPARAM wParam, LPARAM lParam, BOOL isremote) {
	if (!p_recv)
		return;

	p_recv->ProcessMessage(const_cast<ts_msg&>(msg), wParam, lParam, isremote);
}

bool CMsgSender::addUpReceiver(CMsgReceiver* recv) {
    if (upReceivers.count(recv) == 1)
		return false;

    upReceivers.insert(recv);

    for (auto iter = upCache.begin(); iter != upCache.end(); iter++) {
        sendToUp(iter->second, 0, 0, true);
	}
    upCache.clear();
	return true;
}

bool CMsgSender::addDownReceiver(CMsgReceiver* recv) {
    if (downReceivers.count(recv) == 1)
        return false;

    downReceivers.insert(recv);

    for (auto iter = downCache.begin(); iter != downCache.end(); iter++) {
        sendToUp(iter->second, 0, 0, true);
    }
    downCache.clear();
    return true;
}

bool CMsgSender::removeUpReceiver(CMsgReceiver* recv) {
    if (upReceivers.count(recv) == 0)
		return false;

    upReceivers.erase(recv);
	return true;
}

bool CMsgSender::removeDownReceiver(CMsgReceiver* recv) {
    if (downReceivers.count(recv) == 0)
        return false;

    downReceivers.erase(recv);
    return true;
}

void CMsgSender::sendToUp(const ts_msg& msg, WPARAM wParam, LPARAM lParam, bool isRemote) {
    for (auto iter = upReceivers.begin(); iter != upReceivers.end(); iter++) {
		(*iter)->ProcessMessage(const_cast<ts_msg&>(msg), wParam, lParam, isRemote);
	}
}

void CMsgSender::sendToDown(const ts_msg& msg, WPARAM wParam, LPARAM lParam, bool isRemote) {
    for (auto iter = downReceivers.begin(); iter != downReceivers.end(); iter++) {
        (*iter)->ProcessMessage(const_cast<ts_msg&>(msg), wParam, lParam, isRemote);
    }
}
