#include <iostream>
#include <assert.h>
#include "CHubConnection.h"
#include "CSynSocket.h"

using namespace std;

CHubConnection::CHubConnection(void)
    : peerHub(new map<TS_UINT64, CPeerConnection*>) {
	iop_lock_init(&mutex_lock);
}

CHubConnection::~CHubConnection(void) {
	if (isCloned) 
		return;

	allUsers.clear();
	clearMap();
    DESTROY(peerHub);

    iop_lock_destroy(&mutex_lock);
}

void CHubConnection::clearMap(void) {
	if (isCloned)
		return;

	iop_lock(&mutex_lock);
	map<TS_UINT64, CPeerConnection*>::iterator iter;
	for (iter = peerHub->begin(); iter != peerHub->end();) {
		DESTROY(iter->second);
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

bool CHubConnection::addPeer(const TS_UINT64 uid, 
	                         const struct sockaddr_in& peeraddr) {
	if (isCloned)
		return false;
	
	iop_lock(&mutex_lock);
	allUsers.insert(uid);
	bool result;
	CPeerConnection *p = new CPeerConnection(pSocket);
	if (p == NULL)
		result = false;
	else if (p->isValidSocket()) {
		p->setPeer(peeraddr);
		if (peerHub->count(uid) != 0) {
			DESTROY(peerHub->at(uid));
			peerHub->erase(uid);
		}
		peerHub->insert(make_pair(uid, p));
		result = true;
	} else {
		DESTROY(p);
		result = false;
	}
	iop_unlock(&mutex_lock);

    return result;
}

bool CHubConnection::removePeer(const TS_UINT64 uid) {
	if (isCloned)
		return false;

    if (!peerHub->empty()) {
		iop_lock(&mutex_lock);
		auto iter = peerHub->find(uid);
		if (iter != peerHub->end()) {
			DESTROY(iter->second);
			peerHub->erase(iter);
		}
		iop_unlock(&mutex_lock);
	}
	return true;
}

CPeerConnection* CHubConnection::findPeer(const TS_UINT64 uid) {
	CPeerConnection* result;
	iop_lock(&mutex_lock);
	auto iter = peerHub->find(uid);
	if (iter != peerHub->end()) {
		result = iter->second;
	} else {
		result =  NULL;
	}
	iop_unlock(&mutex_lock);
	return result;
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
	for (iter = peerHub->begin(); iter != peerHub->end(); ++iter) {
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

    memset(&m_ToAddr, 0, CAbsSocket::m_LocalAddrSize);
    memset(&m_FromAddr, 0, CAbsSocket::m_LocalAddrSize);
    clearMap();

	return true; //pSocket->closeSocket();
}

int CHubConnection::send(const char* buf, ULONG len) {
	if (!pSocket)
		return -1;

	CPeerConnection* pc;
	int brc = 0;

	iop_lock(&mutex_lock);
	for (auto iter = peerHub->begin(); iter != peerHub->end();) {
        if (NULL == iter->second) {
			peerHub->erase(iter++);
            cout << "warning: detected null socket in CHubConnection::send" << endl;
            ++iter;
			continue;
		}
		pc = iter->second;
		brc += pc->send(buf, len) > 0;
		++iter;
	}
#ifdef _DEBUG_INFO_
	cout << "resend for " << peerHub->size() << "users" << endl;
#endif
	iop_unlock(&mutex_lock);
	return brc;
}

int CHubConnection::sendExcept(const char* buf, ULONG len, TS_UINT64 uid) {
	if (!pSocket)
		return -1;

	CPeerConnection* pc;
	int brc = 0;
	
	map<TS_UINT64, CPeerConnection*>::iterator iter;

	iop_lock(&mutex_lock);
    for (iter = peerHub->begin(); iter != peerHub->end();) {
        if (iter->first == uid) {			// 除了这个UID的，别人都要发 {
            ++iter;
            continue;
        }

        pc = iter->second;
        if (NULL == pc) {
            peerHub->erase(iter++);
            cout << "warning: detected null socket in CHubConnection::sendexcept" << endl;
            ++iter;
            continue;
        }
		brc += pc->send(buf, len) > 0;
        ++iter;
	}
#ifdef _DEBUG_INFO_
	cout << "resend for " << peerHub->size() - 1 << "users" << endl;
#endif
	iop_unlock(&mutex_lock);
	return brc;
}

int CHubConnection::recv(char* buf, ULONG& len) {
	if (!pSocket || !pSocket->isValidSocket())
		return -1;

    int result = pSocket->recvData(buf, len, &m_FromAddr);
    if (result > 0) {
        TS_UINT64 time = getTime(*(ts_msg*)buf);
        if (time > latestTime) {
            latestTime = time;
        }
    } else {
        // TODO when 10054 how can i get correct buf?..
        //if (GetLastError() == 10054) {
        //    peerHub->erase(getUid(*(ts_msg*) buf));
        //}
    }
    return result;
}

void CHubConnection::setPeerConnection(const struct sockaddr_in& peeraddr) {
	if (isCloned)
		return;

	if (!peerHub)
		return;

	//pPeerConnect->setPeer(peeraddr);
}

bool CHubConnection::copy(CAbsConnection* pConn) {
	if (!pConn)
		return false;

	CAbsSocket *ps = pConn->getSocket();
	if (!ps)
		return false;

	assert(ps->getSocket() > 0);

    pSocket->operator=(*ps);

	memcpy(&m_ToAddr, pConn->getPeer(), CAbsSocket::m_LocalAddrSize);

	CHubConnection* pHubConnection = reinterpret_cast<CHubConnection*> (pConn);
	if (NULL != peerHub) {
		clearMap();
	}
	peerHub = pHubConnection->getPeerHub();

	isCloned = true;
	return true;
}
