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

	map<int, CWSServer*> map_workserver;		// classid -> CWSServer
	map<TS_UINT64, UserBase> map_userinfo;		// UID  -> UserBase

	queue<int> port_queue;

public:
	CAgentServer();
	virtual ~CAgentServer();

	void loadUser();
	void createClass(int classid);
	void destroyClass(int classid);
	bool enterClass(sockaddr_in addr, UserBase user);
	void leaveClass(int classid, int uid);
	DWORD MsgHandler(TS_PEER_MESSAGE& pmsg);

private:
	bool isClassExist(int classid);
};


















#endif