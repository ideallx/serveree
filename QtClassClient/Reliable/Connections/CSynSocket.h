#ifndef _CONNECTIONS_SYNSOCKET_H_
#define _CONNECTIONS_SYNSOCKET_H_

#include <string>

#include "../DataUnit/CMessage.h"
#include "CAbsSocket.h"

using namespace std;

class  CSynSocket : public CAbsSocket {
private:
	string ipAddress;

public:
	CSynSocket();
	virtual ~CSynSocket(void) {}

public:
	// port == 0 means you are a client
	// port != 0 server
	bool createSocket(unsigned short iPort = 0);
	bool closeSocket(void);

	int sendData(const char* buf, ULONG len, const struct sockaddr_in* ToAddr);
	int recvData(char* buf, ULONG& len, struct sockaddr_in* FromAddr);

	void setIp(string in) { ipAddress = in; }
    inline string getIpAddress() { return ipAddress; }

private:
	bool bindPort(unsigned short iPort = 0);
};


#endif
