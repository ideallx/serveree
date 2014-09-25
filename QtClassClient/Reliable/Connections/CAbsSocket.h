#ifndef _CONNECTIONS_ABSSOCKET_H_
#define _CONNECTIONS_ABSSOCKET_H_

#pragma once

#include "../OSInedependent/libiop/iop_config.h"
#include "../OSInedependent/libiop/iop_util.h"

#include "../Stdafx.h"

class  CAbsSocket {
protected:
	SOCKET m_Socket;
	struct sockaddr_in m_LocalAddr;
	int	m_LocalAddrSize;

protected:
	int rc;
	int err;
	bool bInit;

public:
	CAbsSocket(void);
	CAbsSocket(const CAbsSocket& that);
	virtual ~CAbsSocket(void);
	bool copy(CAbsSocket* s);

protected:
	virtual bool init(void) = 0;
	virtual void unInit(void) = 0;

public:
	virtual bool createSocket(unsigned short iPort = 0) = 0;
	virtual bool closeSocket(void) = 0;

	virtual int sendData(const char* buf, ULONG len, const struct sockaddr_in* ToAddr) = 0;
	virtual int recvData(char* buf, ULONG& len, struct sockaddr_in* FromAddr) = 0;

public:
	void setSocket(const SOCKET& s);
	SOCKET getSocket(void) const;

	struct sockaddr_in* getLocalAddr(void) const;
	void setLocalAddr(const struct sockaddr_in* addr);

	bool getInitStatus(void) const;
	bool isValidSocket(void) const;

public:
	static TS_UINT64 getAddressKey(const struct sockaddr_in addr);

	int setSockOpt(int level, int optname, const char *optval, int optlen);
	int getSockOpt(int level, int optname, char *optval, socklen_t* optlen);
};


#endif
