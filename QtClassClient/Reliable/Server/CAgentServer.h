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
 * �����������������
 *		1:	���ű�
 *			1.1:	class->WSserver�� map_workserver
 *			1.2:	UID->UserBase�� map_userinfo
 *			1.3:	UID->time�� heartBeatTime
 *			1.4:	�����û���
 *		2:	scan�̣߳�ɨ������û�
 *		3:	���룬�˳������������ٿ���
 *
 *	����/�������ù���:
 *		1:	clientѡ��ĳ��class���룬����enterclass��msg
 *		2:	server�յ������ָ�class��û�д��������򴴽����ã���port_queue�з����µĶ˿ںţ���class����map_workserver
 *		3:	server���ͽ���༶�ɹ���msg��client��client����Ϣ����map_userinfo��
 *		4:	client��ʼ��server��ͣ�ط��ͣ�server��ͣ��ת����
 *
 *	�˳�/���ٿ��ù���:
 *		1:	client�˳�ĳ��class������leaveclass
 *		2:	server�յ��������������һ���ˣ������ٿ��ã��˿ںŷ�����port_queue��class��map_workserver��ɾ��
 *		3:	server�����˳��༶�ɹ�msg��client��client��Ϣ��map_userinfo��ɾ��
 *		4:	����
 *
 *	ɨ����߹���: scanAgent
 *		1:	ÿ���ͻ��˹���ʱ����agent������������������ʱ��
 *		2:	ÿ����������������ʱ�䱣���heartBeatTime
 *		3:	ÿ��һ��ʱ��ɨ�����set
 *		4:	���Ƿ�������3��û�յ���ʱ�����ڼ����3���������offlineUsers����
 *		5:	ÿ���յ�������������uid��offlineUsers�����޳�
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
	map<TS_UINT64, TS_UINT64> heartBeatTime;	// uid->time ���һ��heartbeat����ʱ��

    iop_thread_t pthread_scanoffline;

    set<TS_UINT64> offlineUsers;				// �����û���

public:
	CAgentServer();
	virtual ~CAgentServer();

	void loadUser();

    void enterAgent(TS_PEER_MESSAGE& inputMsg, UserBase user);
	bool enterClass(TS_PEER_MESSAGE& inputMsg, UserBase user);
	void leaveClass(TS_PEER_MESSAGE& inputMsg, UserBase user);
    void createClassResult(TS_PEER_MESSAGE& pmsg, CWSServer* server);

	DWORD MsgHandler(TS_PEER_MESSAGE& pmsg);

	// ��ȡ���е����û�
	int getOfflineUsers(set<TS_UINT64>& out);

	// ɨ�����
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
