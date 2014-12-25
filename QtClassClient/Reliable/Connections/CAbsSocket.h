#ifndef _SOCKET_ABSSOCKET_H_
#define _SOCKET_ABSSOCKET_H_

#include <iop_config.h>
#include <iop_util.h>

#include "../../Stdafx.h"

class  CAbsSocket {
protected:
	io_handle_t         m_Socket;
	struct sockaddr_in  m_LocalAddr;
	bool                bInit;

protected:
	int*				rc;
    int                 err;

public:
	static const int m_LocalAddrSize;

	CAbsSocket(void);
	CAbsSocket(const CAbsSocket& that);
    CAbsSocket& operator=(const CAbsSocket& rhs);

    virtual ~CAbsSocket(void);

public:
	virtual bool createSocket(unsigned short iPort = 0) = 0;
	bool closeSocket(void);

	virtual int sendData(const char* buf, ULONG len, const struct sockaddr_in* ToAddr) = 0;
	virtual int recvData(char* buf, ULONG& len, struct sockaddr_in* FromAddr) = 0;

public:
	inline void setSocket(const SOCKET& s) { if (s != INVALID_SOCKET) m_Socket = s; }
	inline SOCKET getSocket(void) const { return m_Socket; }

	inline struct sockaddr_in getLocalAddr(void) const { return m_LocalAddr; }
	inline void setLocalAddr(const struct sockaddr_in& addr) { m_LocalAddr = addr; }

	inline bool getInitStatus(void) const { return bInit; }
	inline bool isValidSocket(void) const { return m_Socket != INVALID_SOCKET; }

public:
	static TS_UINT64 getAddressKey(const struct sockaddr_in addr);

	inline int setSockOpt(int level, int optname, const char *optval, int optlen) {
		return setsockopt(m_Socket, level, optname, optval, optlen);
	}
	
    inline int getSockOpt(int level, int optname, char *optval, iop_socklen_t* optlen) const {
		return getsockopt(m_Socket, level, optname, optval, optlen);
	}


protected:
    void copy(const CAbsSocket& that);
};


#endif
