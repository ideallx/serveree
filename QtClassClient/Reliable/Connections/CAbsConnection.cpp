#include "CAbsConnection.h"
#include "CSynSocket.h"
#include "../../Stdafx.h"

CAbsConnection::CAbsConnection(void)
	: pSocket(new CSynSocket())
    , isCloned(false)
    , latestTime(0) {
	memset(&m_ToAddr, 0, CAbsSocket::m_LocalAddrSize);
	memset(&m_FromAddr, 0, CAbsSocket::m_LocalAddrSize);
}

CAbsConnection::~CAbsConnection(void) {
    DESTROY(pSocket);
}

void CAbsConnection::setPeer(const struct sockaddr_in& peeraddr) {
	// setPeerConnection(peeraddr);
	memcpy(&m_ToAddr, &peeraddr, CAbsSocket::m_LocalAddrSize);
}
