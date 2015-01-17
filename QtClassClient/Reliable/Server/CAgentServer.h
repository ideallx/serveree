#ifndef _SERVER_CAGENTSERVER_H_
#define _SERVER_CAGENTSERVER_H_

#include <map>
#include <queue>
#include <set>

#include <iop_thread.h>
#include "CServer.h"

struct UserBase;
#include "CWSServer.h"

using namespace std;

/**
 * 代理服务器，包含：
 *		1:	四张表
 *			1.1:	class->WSserver表 map_workserver
 *			1.2:	UID->UserBase表 map_userinfo
 *			1.3:	UID->time表 heartBeatTime
 *			1.4:	掉线用户表
 *		2:	scan线程，扫描掉线用户
 *		3:	加入，退出，创建，销毁课堂
 *
 *	加入/创建课堂过程:
 *		1:	client选择某个class进入，发送enterclass的msg
 *		2:	server收到，发现该class并没有创建过，则创建课堂，从port_queue中分配新的端口号，新class加入map_workserver
 *		3:	server发送进入班级成功的msg给client，client的信息加入map_userinfo中
 *		4:	client开始对server不停地发送，server不停地转发。
 *
 *	退出/销毁课堂过程:
 *		1:	client退出某个class，发送leaveclass
 *		2:	server收到，若发现是最后一个人，则销毁课堂，端口号返还给port_queue，class从map_workserver中删除
 *		3:	server发送退出班级成功msg给client，client信息从map_userinfo中删除
 *		4:	结束
 *
 *	扫描掉线过程: scanAgent
 *		1:	每个客户端过段时间往agent发送心跳包，包括了时间
 *		2:	每次心跳包都将最新时间保存进heartBeatTime
 *		3:	每过一段时间扫描这个set
 *		4:	若是发现连续3次没收到（时间差大于间隔的3倍）则加入offlineUsers表中
 *		5:	每次收到心跳包，都将uid从offlineUsers表中剔除
 *
 */

enum SpecialClassid {
    ClassidNotLogin,
    ClassidNotInclass,
};

class WorkServerInfo {
public:
    WorkServerInfo() : server(NULL), teacherid(0) {}

	virtual ~WorkServerInfo() { delete server; }
public:
    CWSServer*  server;
    TS_UINT64   teacherid;
    unsigned char className[40];
    unsigned char nickname[20];
    int allowedStudentNum;
};

class CAgentServer : public CServer {
private:
	iop_lock_t lockWorkServer;
	iop_lock_t lockPortqueue;
	iop_lock_t lockOfflineMaps;

    map<TS_UINT64, WorkServerInfo*> map_workserver;	// classid -> CWSServer
	map<TS_UINT64, UserBase> map_userinfo;		// UID  -> UserBase
	map<string, TS_UINT64> map_alluser;			// username -> UID

	queue<int> port_queue;
	map<TS_UINT64, TS_UINT64> heartBeatTime;	// uid->time 最近一次heartbeat包的时间

    iop_thread_t pthread_scanoffline;

    set<TS_UINT64> offlineUsers;				// 掉线用户表

public:
	CAgentServer();
	virtual ~CAgentServer();

	void loadUser();

    void enterAgent(TS_PEER_MESSAGE& inputMsg, UserBase user);
	bool enterClass(TS_PEER_MESSAGE& inputMsg, UserBase user);
	void leaveClass(TS_PEER_MESSAGE& inputMsg, UserBase user);
    void createClassResult(TS_PEER_MESSAGE& pmsg, CWSServer* server);

	DWORD MsgHandler(TS_PEER_MESSAGE& pmsg);

	// 获取所有掉线用户
	int getOfflineUsers(set<TS_UINT64>& out);

	// 扫描掉线
    void scanAgent();


    CWSServer* getServerByUID(TS_UINT64 uid);
    CWSServer* getServerByClassid(TS_UINT64 classid);

	bool Start(unsigned short port = 0);

    bool isClassExist(TS_UINT64 classid);

    WORD checkUsernamePassword(UserBase &user);

    void sendToQueue(TS_PEER_MESSAGE& pmsg, unsigned char type, WORD size);

    void sendAllClassesInfo(TS_PEER_MESSAGE& pmsg, TS_UINT64 uid);

private:
	void userLoginNotify(TS_PEER_MESSAGE& msg, TS_UINT64 uid);
    void userLogoutNotify(TS_PEER_MESSAGE& msg, TS_UINT64 uid);
    void sendUserList(TS_PEER_MESSAGE& pmsg, CWSServer *pServer);

    CWSServer *createClass();
	void destroyClass(TS_UINT64 classid);

    void sendLeaveSuccess(TS_PEER_MESSAGE& pmsg, MsgResult result = SuccessLeaveClass);

    friend thread_ret_type thread_func_call scanOfflineProc(LPVOID lpParam);
};

#endif
