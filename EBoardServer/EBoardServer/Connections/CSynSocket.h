#ifndef _CONNECTIONS_SYNSOCKET_H_
#define _CONNECTIONS_SYNSOCKET_H_

#include "CAbsSocket.h"

class  CSynSocket : public CAbsSocket {
public:
	CSynSocket(void);
	virtual ~CSynSocket(void);

protected:
	bool init(void);
	void unInit(void);

public:
	bool createSocket(unsigned short iPort = 0);
	bool closeSocket(void);
	int sendData(const char* buf, ULONG len, const struct sockaddr_in* ToAddr);
	int recvData(char* buf, ULONG& len, struct sockaddr_in* FromAddr);

private:
	bool bindPort(unsigned short iPort);
};


#endif