#ifndef _CONNECTIONS_CONNECTION_H_
#define _CONNECTIONS_CONNECTION_H_

#include "CAbsConnection.h"

class CConnection : public CAbsConnection {
public:
	CConnection(void) {}
	virtual ~CConnection(void);

public:
	bool create(unsigned short localport = 0);
	bool clear(void);
	int send(const char* buf, ULONG len);
	int recv(char* buf, ULONG& len);

protected:
	inline void setPeerConnection(const struct sockaddr_in& peeraddr) { m_ToAddr = peeraddr; }
};


#endif