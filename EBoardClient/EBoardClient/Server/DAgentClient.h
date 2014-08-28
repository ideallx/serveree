#ifndef _SERVER_DAGENTCLIENT_H_
#define _SERVER_DAGENTCLIENT_H_

#include <map>
#include <queue>

#include <iop_thread.h>

class CWSServer;

#include "../DataUnit/UserBase.h"
#include "DWSClient.h"

using namespace std;

class DAgentClient : public CServer {
private:
	map<TS_UINT64, DWSClient*> workClients;		// classid -> CWSServer
	UserBase* ub;

public:
	DAgentClient();
	virtual ~DAgentClient();

	bool Start(unsigned short port = 0);

	DWORD MsgHandler(TS_PEER_MESSAGE& pmsg);

	void sendProc();

	void setUser(UserBase& ubin);

private:
	bool isClassExist(TS_UINT64 classid);
	
	bool enterClass(ts_msg& msg);

	bool leaveClass(TS_UINT64 classid);
};

#endif