#ifndef _SERVER_DWSCLIENT_H_
#define _SERVER_DWSCLIENT_H_

#include <set>
#include <map>

#include <semaphore.h>

#include "CServer.h"
#include "../Connections/CHubConnection.h"
#include "../DataUnit/CBlockManager.h"


class DWSClient : public CServer {
private:
	TS_UINT64 _classid;
	TS_UINT64 _reserved;

public:
	DWSClient(TS_UINT64 classid, TS_UINT64 reserved);
	virtual ~DWSClient();
	bool Start(unsigned short port); 
	void generateData();

public:
	void sendProc();
	void recvProc();
	void msgProc();

friend void* GenProc(LPVOID lpParam);

private:
	int seq;
	int _uid;
	static int clientUid;

};

#endif /* CWSSERVER_H_ */
