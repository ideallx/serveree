/*
 * CWSServer.cpp
 *
 *  Created on: Jun 21, 2014
 *      Author: root
 */

#include "DWSClient.h"
#include "../Connections/CReliableConnection.h"

DWSClient::DWSClient(TS_UINT64 classid, TS_UINT64 reserved) :
	_classid(classid),
	_reserved(reserved) {
		dynamic_cast<CReliableConnection*>(pConnect)->switchSendCache(true);		// client端在send的时候保存
}

DWSClient::~DWSClient() {

}


void DWSClient::recvProc() {
	ULONG msglen = sizeof(ts_msg);
	TS_PEER_MESSAGE *pmsg = new TS_PEER_MESSAGE();
	memset(pmsg, 0, sizeof(TS_PEER_MESSAGE));
	
	while (isRunning()) {
		if (pConnect->recv(pmsg->msg.Body, msglen) > 0) {
			// memcpy(&pmsg->peeraddr, pConnect->getRecvAddr(), sizeof(struct sockaddr_in));
			WriteIn(*pmsg);
		}
	}
	return;

	delete pmsg;
	cout << "recv thread exit" << endl;
}

void DWSClient::msgProc() {
	TS_PEER_MESSAGE *pmsg = new TS_PEER_MESSAGE();
	memset(pmsg, 0, sizeof(TS_PEER_MESSAGE));

	while (isRunning()) {
		memset(pmsg, 0, sizeof(TS_PEER_MESSAGE));
		ReadIn(*pmsg);
		MsgHandler(*pmsg);
	}
	delete pmsg;
}

void DWSClient::sendProc() {
	TS_PEER_MESSAGE *pmsg = new TS_PEER_MESSAGE();
	memset(pmsg, 0, sizeof(TS_PEER_MESSAGE));

	while (isRunning()) {
		ReadOut(*pmsg);
		pConnect->send(pmsg->msg.Body, packetSize(pmsg->msg));
	}
	delete pmsg;
	cout << "send thread exit" << endl;
}