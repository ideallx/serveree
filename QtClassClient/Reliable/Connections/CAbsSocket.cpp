#include "CAbsSocket.h"

const int CAbsSocket::m_LocalAddrSize = sizeof(struct sockaddr_in);

CAbsSocket::CAbsSocket(void)
	: m_Socket(INVALID_SOCKET)
	, bInit(false)

	, rc(0)
    , err(0) {
}

CAbsSocket::~CAbsSocket() {
    // closeSocket();
}

#include <iostream>
using namespace std;
bool CAbsSocket::closeSocket(void) {
    if (0 == iop_close_handle(m_Socket)) {
		return true;
    } else {
		int b = GetLastError();
		cout << "close socket error" << GetLastError();
		return false;
	}
}

bool CAbsSocket::copy(CAbsSocket* s) {
	if (!s)
		return false;

	m_Socket = s->m_Socket;
	m_LocalAddr = s->m_LocalAddr;
	bInit = s->bInit;

	return true;
}

CAbsSocket::CAbsSocket(const CAbsSocket& that) {
	m_Socket = that.m_Socket;
	m_LocalAddr = that.m_LocalAddr;
	bInit = that.bInit;
}

// example 192 168 1 128 7780  0xC0 A8 01 CA 1E64
TS_UINT64 CAbsSocket::getAddressKey(const struct sockaddr_in addr) {
	TS_UINT64 key;

	key = addr.sin_addr.s_addr;
	key = key << 16;
	key = key + addr.sin_port;

	return key;
}
