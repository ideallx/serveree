#include "CAbsSocket.h"

CAbsSocket::CAbsSocket(void) :
	m_Socket(INVALID_SOCKET),
	m_LocalAddrSize(sizeof(m_LocalAddr)),
	rc(0),
	err(0),
	bInit(false) {
}

CAbsSocket::~CAbsSocket(void) {

}

bool CAbsSocket::copy(CAbsSocket* s) {
	if (!s)
		return FALSE;

	m_Socket = s->getSocket();
	setLocalAddr(s->getLocalAddr());
	bInit = s->getInitStatus();

	return TRUE;
}

CAbsSocket::CAbsSocket(const CAbsSocket& that) {
	m_Socket = that.m_Socket;
	memcpy(&m_LocalAddr, &(that.m_LocalAddr), 
		sizeof(struct sockaddr_in));
	bInit = that.bInit;
}

void CAbsSocket::setSocket(const SOCKET& s) {
	if (s != INVALID_SOCKET)
		m_Socket = s;
}

SOCKET CAbsSocket::getSocket(void) const {
	return m_Socket;
}

bool CAbsSocket::isValidSocket(void) const {
	return m_Socket != INVALID_SOCKET;
}

struct sockaddr_in* CAbsSocket::getLocalAddr(void) const {
	return (struct sockaddr_in*) &m_LocalAddr;
}

void CAbsSocket::setLocalAddr(const struct sockaddr_in* addr) {
	memcpy(&m_LocalAddr, addr, sizeof(struct sockaddr_in));
}

bool CAbsSocket::getInitStatus(void) const {
	return bInit;
}

int CAbsSocket::setSockOpt(int level, int optname, const char *optval, int optlen) {
	return setsockopt(m_Socket, level, optname, optval, optlen);
}

int CAbsSocket::getSockOpt(int level, int optname, char *optval, socklen_t* optlen) {
	return getsockopt(m_Socket, level, optname, optval, optlen);
}

// example 192 168 1 202 7780  0xC0 A8 01 CA 1E64
TS_UINT64 CAbsSocket::getAddressKey(const struct sockaddr_in addr) {
	TS_UINT64 key;

	key = addr.sin_addr.s_addr;
	key = key << 16;
	key = key + addr.sin_port;

	return key;
}