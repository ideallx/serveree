#include "CAbsConnection.h"
#include "CSynSocket.h"

CAbsConnection::CAbsConnection(void) {
	pSocket = new CSynSocket();
	memset(&m_ToAddr, 0, sizeof(struct sockaddr_in));
	memset(&m_FromAddr, 0, sizeof(struct sockaddr_in));

	isCloned = FALSE;
}

CAbsConnection::~CAbsConnection(void) {
	DESTROY(pSocket);
}


CAbsSocket* CAbsConnection::getSocket(void) const {
	return pSocket;
}

bool CAbsConnection::setSocket(CAbsSocket* ps) {
	return pSocket->copy(ps);
}

bool CAbsConnection::isValidSocket() {
	if (!pSocket)
		return false;

	return pSocket->isValidSocket();
}

struct sockaddr_in* CAbsConnection::getPeer(void) const {
	return (struct sockaddr_in*) &m_ToAddr;
}

struct sockaddr_in* CAbsConnection::getRecvAddr(void) const {
	return (struct sockaddr_in*) &m_FromAddr;
}

void CAbsConnection::setPeer(const struct sockaddr_in& peeraddr) {
	setPeerConnection(peeraddr);
	memcpy(&m_ToAddr, &peeraddr, sizeof(struct sockaddr_in));
}
