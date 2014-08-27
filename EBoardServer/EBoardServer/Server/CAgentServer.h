#ifndef _SERVER_CAGENTSERVER_H_
#define _SERVER_CAGENTSERVER_H_

#include <map>
#include <queue>

#include <iop_thread.h>

class CWSServer;

#include "../DataUnit/UserBase.h"
#include "CServer.h"

using namespace std;

class CAgentServer : public CServer {
private:
	iop_lock_t lockWorkServer;
	iop_lock_t lockPortqueue;

	map<TS_UINT64, CWSServer*> map_workserver;	// classid -> CWSServer
	map<TS_UINT64, UserBase> map_userinfo;		// UID  -> UserBase

	queue<int> port_queue;

public:
	CAgentServer();
	virtual ~CAgentServer();

	void loadUser();

	void createClass(TS_UINT64 classid);
	void destroyClass(TS_UINT64 classid);
	bool enterClass(TS_PEER_MESSAGE& inputMsg, UserBase user);
	void leaveClass(TS_UINT64 classid, TS_UINT64 uid);

	DWORD MsgHandler(TS_PEER_MESSAGE& pmsg);

private:
	bool isClassExist(TS_UINT64 classid);
};

#endif