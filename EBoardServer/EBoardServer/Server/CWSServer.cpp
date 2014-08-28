/*
 * CWSServer.cpp
 *
 *  Created on: Jun 21, 2014
 *      Author: root
 */

#include "CWSServer.h"
#include "../Connections/CReliableConnection.h"

CWSServer::CWSServer(TS_UINT64 classid, TS_UINT64 reserved) :
	_classid(classid),
	_reserved(reserved) {
}

CWSServer::~CWSServer() {

}

void CWSServer::displayPeer(){
	cout << "Now in the hub : ----------------------------" << endl;
	((CReliableConnection*) pConnect)->display();
	cout << "---------------------------------------------" << endl;
}

bool CWSServer::addPeer(sockaddr_in addr, TS_UINT64 uid) {
	return dynamic_cast<CReliableConnection*>(pConnect)->addPeer(uid, addr);
}

bool CWSServer::removePeer(TS_UINT64 uid) {
	return dynamic_cast<CReliableConnection*>(pConnect)->removePeer(uid);
}

void CWSServer::removeUser(TS_UINT64 uid) {
	dynamic_cast<CReliableConnection*>(pConnect)->saveUserBlock(uid);
	removePeer(uid);
}

bool CWSServer::isEmpty() {
	return dynamic_cast<CReliableConnection*>(pConnect)->getPeerHub()->size() == 0;
}

void CWSServer::recvProc() {
	ULONG msglen = sizeof(ts_msg);
	TS_PEER_MESSAGE *pmsg = new TS_PEER_MESSAGE();
	memset(pmsg, 0, sizeof(TS_PEER_MESSAGE));
	
	while (isRunning()) {
		if (pConnect->recv(pmsg->msg.Body, msglen) > 0) {
			WriteIn(*pmsg);
		}
	}
	return;

	delete pmsg;
	cout << "recv thread exit" << endl;
}

void CWSServer::msgProc() {
	TS_PEER_MESSAGE *pmsg = new TS_PEER_MESSAGE();
	memset(pmsg, 0, sizeof(TS_PEER_MESSAGE));

	while (isRunning()) {
		memset(pmsg, 0, sizeof(TS_PEER_MESSAGE));
		ReadIn(*pmsg);
		MsgHandler(*pmsg);
	}
	delete pmsg;
}

void CWSServer::sendProc() {
	TS_PEER_MESSAGE *pmsg = new TS_PEER_MESSAGE();
	memset(pmsg, 0, sizeof(TS_PEER_MESSAGE));

	while (isRunning()) {
		ReadOut(*pmsg);
		pConnect->send(pmsg->msg.Body, packetSize(pmsg->msg));
	}
	delete pmsg;
	cout << "send thread exit" << endl;
}