#include <iostream>
#include <assert.h>
#include "CHubConnection.h"
#include "CSynSocket.h"

using namespace std;

CHubConnection::CHubConnection(void) : 
	pPeerConnect(NULL),
	peerHub(new map<TS_UINT64, CPeerConnection*>) {
	iop_lock_init(&mutex_lock);
}

CHubConnection::~CHubConnection(void) {
	if (isCloned) 
		return;

    clear();
    DESTROY(peerHub);
    DESTROY(pSocket);

    iop_lock_destroy(&mutex_lock);
}

void CHubConnection::clearMap(void) {
	if (isCloned)
		return;
	iop_lock(&mutex_lock);
	map<TS_UINT64, CPeerConnection*>::iterator iter;
	for (iter = peerHub->begin(); iter != peerHub->end();) {
		DESTROY((*iter).second);
		peerHub->erase(iter++);
	}
	iop_unlock(&mutex_lock);
}

int CHubConnection::size(void){
	iop_lock(&mutex_lock);
	int size = peerHub->size();
	iop_unlock(&mutex_lock);
	return size;
}

bool CHubConnection::addPeer(const struct sockaddr_in& peeraddr) {
	if (isCloned)
		return false;

	pPeerConnect = new CPeerConnection(pSocket);
	pPeerConnect->copy(this);
	assert(pPeerConnect->getSocket()->getSocket() > 0);

	iop_lock(&mutex_lock);
	pPeerConnect->setPeer(peeraddr);
	if ((*peerHub).count(pSocket->getAddressKey(peeraddr)) == 0) {
		(*peerHub)[pSocket->getAddressKey(peeraddr)] = pPeerConnect;
	} else {
		delete pPeerConnect;
	}
	iop_unlock(&mutex_lock);
	return true;
}

bool CHubConnection::addPeer(const TS_UINT64 uid, 
	                         const struct sockaddr_in& peeraddr) {
	if (isCloned)
		return false;

	allUsers.insert(uid);

	pPeerConnect = new CPeerConnection(pSocket);
	pPeerConnect->copy(this);
	assert(pPeerConnect->getSocket()->getSocket() > 0);

	iop_lock(&mutex_lock);
	pPeerConnect->setPeer(peeraddr);
	if ((*peerHub).count(uid) == 0) {
		(*peerHub)[uid] = pPeerConnect;
	} else {
		delete (*peerHub)[uid];
		(*peerHub)[uid] = pPeerConnect;
	}
	iop_unlock(&mutex_lock);
	return true;
}

bool CHubConnection::removePeer(const struct sockaddr_in& peeraddr) {
	if (isCloned)
		return false;

	if (size() > 0) {
		iop_lock(&mutex_lock);
		CPeerConnection* temp = (*peerHub)[pSocket->getAddressKey(peeraddr)];
		DESTROY(temp);
		peerHub->erase(pSocket->getAddressKey(peeraddr));
		iop_unlock(&mutex_lock);
	}
	return TRUE;
}

bool CHubConnection::removePeer(const TS_UINT64 uid) {
	if (isCloned)
		return false;

	if (size() > 0) {
		iop_lock(&mutex_lock);
		CPeerConnection* temp = (*peerHub)[uid];
		DESTROY(temp);
		peerHub->erase(uid);
		iop_unlock(&mutex_lock);
	}
	return TRUE;
}

CPeerConnection* CHubConnection::findPeer(const struct sockaddr_in& peeraddr) {
	map<TS_UINT64, CPeerConnection*>::iterator iter;
	iop_lock(&mutex_lock);
	iter = peerHub->find(pSocket->getAddressKey(peeraddr));

	if (iter != peerHub->end()) {
		iop_unlock(&mutex_lock);
		return iter->second;
	} else {
		iop_unlock(&mutex_lock);
		return NULL;
	}
}

CPeerConnection* CHubConnection::findPeer(const TS_UINT64 uid) {
	map<TS_UINT64, CPeerConnection*>::iterator iter;
	iop_lock(&mutex_lock);
	iter = peerHub->find(uid);

	if (iter != peerHub->end()) {
		iop_unlock(&mutex_lock);
		return iter->second;
	} else {
		iop_unlock(&mutex_lock);
		return NULL;
	}
}

bool CHubConnection::create(unsigned short localport) {
	if (!pSocket)
		pSocket = new CSynSocket();

	if (!pSocket->createSocket(localport))
		return false;
	else
		return true;
}

void CHubConnection::display() {
	iop_lock(&mutex_lock);
	map<TS_UINT64, CPeerConnection*>::iterator iter;
	for (iter = peerHub->begin(); iter != peerHub->end(); iter++) {
		cout << inet_ntoa((*iter).second->getPeer()->sin_addr) << " " 
			<< htons((*iter).second->getPeer()->sin_port) << endl;
	}
	iop_unlock(&mutex_lock);
}

bool CHubConnection::clear(void){
    if (isCloned)
        return true;

    if (!pSocket)
        return true;

    bool brc = true;

    memset(&m_ToAddr, 0, sizeof(struct sockaddr_in));
    memset(&m_FromAddr, 0, sizeof(struct sockaddr_in));

    brc = pSocket->closeSocket();

    clearMap();

	return brc;
}

int CHubConnection::send(const char* buf, ULONG len) {
	if (!pSocket)
		return -1;

	CPeerConnection* pc;
	int brc = 0;
	//cout << "debug: total peers# is: " << size() << endl;
	map<TS_UINT64, CPeerConnection*>::iterator iter;

	iop_lock(&mutex_lock);
	for (iter = peerHub->begin(); iter != peerHub->end(); iter++) {
		pc = iter->second;
		brc = pc->send(buf, len);
	}
	iop_unlock(&mutex_lock);
	return brc;
}

int CHubConnection::sendExcept(const char* buf, ULONG len, TS_UINT64 uid) {
	if (!pSocket)
		return -1;

	CPeerConnection* pc;
	int brc = 0;
	
	//cout << "debug: total peers# is: " << size() << endl;
	map<TS_UINT64, CPeerConnection*>::iterator iter;

	iop_lock(&mutex_lock);
	for (iter = peerHub->begin(); iter != peerHub->end(); iter++) {
		if (iter->first == uid)			// 除了这个UID的，别人都要发
			continue;
		pc = iter->second;
		brc = pc->send(buf, len);
	}
	iop_unlock(&mutex_lock);
	return brc;
}

int CHubConnection::recv(char* buf, ULONG& len) {
	if (!pSocket)
		return -1;

	//cout << "1";
	return pSocket->recvData(buf, len, &m_FromAddr);
}

void CHubConnection::setPeerConnection(const struct sockaddr_in& peeraddr) {
	if (isCloned)
		return;

	if (!peerHub)
		return;

	removePeer(m_ToAddr);
	addPeer(peeraddr);
}

bool CHubConnection::copy(CAbsConnection* pConn) {
	if (!pConn)
		return false;

	CAbsSocket *ps = pConn->getSocket();
	if (!ps)
		return false;

	assert(ps->getSocket() > 0);
	if (pSocket->copy(ps)) {
		memcpy(&m_ToAddr, pConn->getPeer(), sizeof(struct sockaddr_in));

		CHubConnection* pHubConnection = (CHubConnection*) pConn;
		if (NULL != peerHub) {
			clearMap();
		}
		peerHub = pHubConnection->getPeerHub();

		isCloned = true;
		return true;
	} else
		return false;
}
