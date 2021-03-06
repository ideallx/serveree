#include "CConnection.h"
#include "CSynSocket.h"

#include <iostream>

CConnection::CConnection(void) {

}

CConnection::~CConnection(void) {
	if (!isCloned) {
		clear();
	}
}

bool CConnection::create(unsigned short localport) {
	if (pSocket != NULL) {
		pSocket = new CSynSocket();
	}

	if (!pSocket->createSocket(localport)) {
		pSocket->closeSocket();
		return false;
	} else
		return true;
}

bool CConnection::clear(void) {
	if (isCloned)
		return true;

	if (pSocket == NULL)
		return true;

	bool brc = true;

	memset(&m_ToAddr, 0, sizeof(struct sockaddr_in));
	memset(&m_FromAddr, 0, sizeof(struct sockaddr_in));

	brc = pSocket->closeSocket();
	DESTROY(pSocket);

	return brc;
}

int CConnection::send(const char* buf, ULONG len) {
	if (!pSocket)
		return -1;
	
	cout << "0";
	return pSocket->sendData(buf, len, &m_ToAddr);
}

int CConnection::recv(char* buf, ULONG& len) {
	if (!pSocket)
		return -1;
	
	cout << "1";
	return pSocket->recvData(buf, len, &m_FromAddr);
}

void CConnection::setPeerConnection(const struct sockaddr_in& peeraddr) {
	return;
}

bool CConnection::copy(CAbsConnection* conn) {
	if (NULL == conn)
		return false;

	CAbsSocket *ps = conn->getSocket();
	if (NULL == ps)
		return false;

	if (pSocket->copy(ps)) {
		memcpy(&m_ToAddr, conn->getPeer(), sizeof(struct sockaddr_in));
		isCloned = true;
		return true;
	}
	return false;
}
