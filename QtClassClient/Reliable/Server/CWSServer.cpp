#include <string>

#include "CWSServer.h"
#include "../Connections/CReliableConnection.h"

CWSServer::CWSServer(TS_UINT64 classid, TS_UINT64 reserved) :
	_classid(classid),
	_reserved(reserved) {
	TS_UINT64 clientTime = getServerTime();
    conn = dynamic_cast<CReliableConnection*> (pConnect);
	conn->setFilePrefix(int2string(classid) + "_" + int2string(clientTime));
}

CWSServer::~CWSServer() {

}

void CWSServer::displayPeer(){
	cout << "Now in the hub : ----------------------------" << endl;
	((CReliableConnection*) pConnect)->display();
	cout << "---------------------------------------------" << endl;
}

bool CWSServer::addPeer(sockaddr_in addr, TS_UINT64 uid) {
	return conn->addPeer(uid, addr);
}

bool CWSServer::removePeer(TS_UINT64 uid) {
	return conn->removePeer(uid);
}

void CWSServer::removeUser(TS_UINT64 uid) {
	dynamic_cast<CReliableConnection*>(pConnect)->saveUserBlock(uid);
	removePeer(uid);
}

bool CWSServer::isEmpty() {
	return conn->getPeerHub()->size() == 0;
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
        if (ReadIn(*pmsg))
            MsgHandler(*pmsg);
	}
	delete pmsg;
}

DWORD CWSServer::MsgHandler(TS_PEER_MESSAGE& pmsg) {
    TS_UINT64 uid = getUid(pmsg.msg);
    if (conn->findPeer(uid) == NULL) {
        conn->addPeer(uid, pmsg.peeraddr);
    }
    return 0;
}

void CWSServer::sendProc() {
	TS_PEER_MESSAGE *pmsg = new TS_PEER_MESSAGE();
	memset(pmsg, 0, sizeof(TS_PEER_MESSAGE));

	while (isRunning()) {
        if (!ReadOut(*pmsg))
            continue;
		pConnect->send(pmsg->msg.Body, packetSize(pmsg->msg));
	}
	delete pmsg;
	cout << "send thread exit" << endl;
}

void CWSServer::sendMaxSeqList() {
    conn->sendMaxSeqList();
}

TS_UINT64 CWSServer::getMaxSeqOfUID(TS_UINT64 uid) {
    return conn->maxSeq(uid);
}
