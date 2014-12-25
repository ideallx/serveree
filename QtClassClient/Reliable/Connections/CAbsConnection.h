#ifndef _CONNECTIONS_ABSCONNECTION_H_
#define _CONNECTIONS_ABSCONNECTION_H_

#include "CSynSocket.h"
#include "../DataUnit/CMessage.h"

// peer ==> Send ==> toAddr
// recv ==> Recv ==> fromAddr

class CAbsConnection {
protected:
	CAbsSocket*         pSocket;
	bool                isCloned;
	struct sockaddr_in  m_ToAddr;
	struct sockaddr_in  m_FromAddr;
    TS_UINT64           latestTime;

public:
	CAbsConnection(void);
	virtual ~CAbsConnection(void);

public:
	inline CAbsSocket* getSocket(void) const { return pSocket; }
	inline void setSocket(const CAbsSocket& ps) { pSocket->operator=(ps); }

	inline bool isValidSocket() { if (!pSocket) return false; return pSocket->isValidSocket(); }

	inline struct sockaddr_in* getPeer(void) const { return (struct sockaddr_in*) &m_ToAddr; }
	void setPeer(const struct sockaddr_in& peeraddr);

	inline struct sockaddr_in* getRecvAddr(void) const { return (struct sockaddr_in*) &m_FromAddr; }
	inline void setRecvAddr(const struct sockaddr_in &addr) { m_FromAddr = addr; }

    inline TS_UINT64 getLatestRecvTime(void) const { return latestTime; }

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
