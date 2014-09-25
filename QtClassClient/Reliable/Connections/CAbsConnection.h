#ifndef _CONNECTIONS_ABSCONNECTION_H_
#define _CONNECTIONS_ABSCONNECTION_H_

#include "CSynSocket.h"
#include "../DataUnit/CMessage.h"

class CAbsConnection {
protected:
	CAbsSocket* pSocket;
	bool isCloned;
	struct sockaddr_in m_ToAddr;
	struct sockaddr_in m_FromAddr;

public:
	CAbsConnection(void);
	CAbsConnection(TS_UINT64 classid);
	virtual ~CAbsConnection(void);

public:
	CAbsSocket* getSocket(void) const;
	bool setSocket(CAbsSocket* ps);

	bool isValidSocket();

	struct sockaddr_in* getPeer(void) const;
	void setPeer(const struct sockaddr_in& peeraddr);

	struct sockaddr_in* getRecvAddr(void) const;

public:
	virtual bool copy(CAbsConnection* conn) = 0;

public:
	virtual bool create(unsigned short localport = 0) = 0;
	virtual bool clear(void) = 0;
	virtual int send(const char* buf, ULONG len) = 0;
	virtual int recv(char* buf, ULONG& len) = 0;

	int send(TS_PEER_MESSAGE pmsg);

protected:
	virtual void setPeerConnection(const struct sockaddr_in& peeraddr) = 0;
};

#endif