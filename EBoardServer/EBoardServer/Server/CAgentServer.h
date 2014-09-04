#ifndef _SERVER_CAGENTSERVER_H_
#define _SERVER_CAGENTSERVER_H_

#include <map>
#include <queue>
#include <set>

#include <iop_thread.h>
#include "CServer.h"

struct UserBase;
class CWSServer;

using namespace std;

class CAgentServer : public CServer {
private:
	iop_lock_t lockWorkServer;
	iop_lock_t lockPortqueue;
	iop_lock_t lockOfflineMaps;

	map<TS_UINT64, CWSServer*> map_workserver;	// classid -> CWSServer
	map<TS_UINT64, UserBase> map_userinfo;		// UID  -> UserBase

	queue<int> port_queue;
	map<TS_UINT64, TS_UINT64> heartBeatTime;	// uid->time 最近一次heartbeat包的时间

	pthread_t scanThread;						// 扫描心跳包线程
	set<TS_UINT64> offlineUsers;				// 掉线用户表

public:
	CAgentServer();
	virtual ~CAgentServer();

	// 从文件加载用户，现在一般不用这个方式
	void loadUser();

	void createClass(TS_UINT64 classid);
	void destroyClass(TS_UINT64 classid);
	bool enterClass(TS_PEER_MESSAGE& inputMsg, UserBase user);
	void leaveClass(TS_PEER_MESSAGE& inputMsg, UserBase user);

	DWORD MsgHandler(TS_PEER_MESSAGE& pmsg);

	// 获取所有掉线用户
	int getOfflineUsers(set<TS_UINT64>& out);

	// 扫描掉线
	void scanOffline();

private:
	bool isClassExist(TS_UINT64 classid);

	friend void* scanOfflineProc(LPVOID lpParam);
};

#endif