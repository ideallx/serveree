#include <iostream>
#include <string>

#include "CAgentServer.h"
#include "CWSServer.h"
#include "../DataUnit/UserBase.h"

using namespace std;

CAgentServer::CAgentServer() {
	iop_lock_init(&lockWorkServer);
	iop_lock_init(&lockPortqueue);
	iop_lock_init(&lockOfflineMaps);
	
	iop_lock(&lockPortqueue);
	for(int i = 10000; i < 20000; i++){
		port_queue.push(i);
	}
	iop_unlock(&lockPortqueue);
}

CAgentServer::~CAgentServer() {
	iop_lock_destroy(&lockOfflineMaps);
	iop_lock_destroy(&lockWorkServer);
	iop_lock_destroy(&lockPortqueue);
}

bool CAgentServer::isClassExist(TS_UINT64 classid) {
	return (map_workserver.count(classid) > 0) && 
		(map_workserver[classid] != NULL);
}

void CAgentServer::loadUser() {
	FILE* fp = freopen("User.txt", "r", stdin);
	assert(fp != NULL);
	UserBase user;
	int cnt = 0;
	cin >> cnt;
	while (cnt-- > 0) {
		user._reserved = 0;
		cin >> user._username >> user._password >> user._uid 
			>> user._classid  >> user._role;
		cout << user;
	}
	fclose(stdin);
}

void CAgentServer::createClass(TS_UINT64 classid) {
	iop_lock(&lockWorkServer);

	iop_lock(&lockPortqueue);				// ��ȡһ��δ�ù��Ķ˿ں�
	int port = port_queue.front();
	port_queue.pop();
	iop_unlock(&lockPortqueue);

	CWSServer* pWorker = new CWSServer(classid, 1);		// ����һ���µ�WorkServer
	map_workserver[classid] = pWorker;
	pWorker->Start(port);

	cout << "Worker Server Start successfully on Port " << port << "." << endl;
	iop_unlock(&lockWorkServer);
}

void CAgentServer::destroyClass(TS_UINT64 classid) {
	iop_lock(&lockWorkServer);

	CWSServer* pServer = map_workserver[classid];
	if (NULL == pServer)
		return;
	int port = pServer->getPort();		// ��ȡ�������˿�
	delete pServer;
	cout << "Worker Server Stop successfully on Port " << port << "." << endl;
	map_workserver[classid] = NULL;
	map_workserver.erase(classid);
		
	iop_lock(&lockPortqueue);
	port_queue.push(port);				// �������˿ڶ���
	iop_unlock(&lockPortqueue);

	iop_unlock(&lockWorkServer);
}

void CAgentServer::scanOffline() {
	TS_UINT64 currentTime = getServerTime();
	
	iop_lock(&lockOfflineMaps);
	int maxAllowedInterval = HeartBeatInterval * 3;
	for (auto iter = heartBeatTime.begin(); iter != heartBeatTime.end(); ) {
		if (currentTime - iter->second > maxAllowedInterval) {
			offlineUsers.insert(iter->first);
		}
		iter++;
	}
	iop_unlock(&lockOfflineMaps);
}

bool CAgentServer::enterClass(TS_PEER_MESSAGE& inputMsg, UserBase user) {
	if (!isClassExist(user._classid)) {								// ��һ���û����룬�򴴽��༶
		createClass(user._classid);
	}
	
	iop_lock(&lockWorkServer);
	CWSServer* pServer = map_workserver[user._classid];
	pServer->addPeer(inputMsg.peeraddr, user._uid);					// ����ĵ�ַ��client agent�Ķ˿ڵ�ַ
	iop_unlock(&lockWorkServer);

	DOWN_AGENTSERVICE* down = (DOWN_AGENTSERVICE*) &inputMsg.msg;	// ����༶�ɹ����ѷ�������Ϣ���߿ͻ���
	down->result = SuccessEnterClass;
	down->addr = *pServer->getServerAddr();							// server�ĵ�ַ���뵽������
	down->head.time = getServerTime();
	down->head.UID = ServerUID;
	WriteOut(inputMsg);

	cout << "Add User: " << user._uid << "into class" << user._classid << endl; 
	map_userinfo.insert(make_pair(user._uid, user));
	heartBeatTime.insert(make_pair(user._uid, down->head.time));
	return true;
}

void CAgentServer::leaveClass(TS_PEER_MESSAGE& inputMsg, UserBase user) {
	iop_lock(&lockWorkServer);
	TS_UINT64 classid = user._classid;
	CWSServer* pServer = map_workserver[classid];
	if (pServer != NULL) {											// server��ɾ������û�
		pServer->removeUser(user._uid);
	}
	iop_unlock(&lockWorkServer);

	DOWN_AGENTSERVICE* down = (DOWN_AGENTSERVICE*) &inputMsg.msg;	// �˳��༶�ɹ����ѷ�������Ϣ���߿ͻ���
	down->result = SuccessLeaveClass;
	down->addr = inputMsg.peeraddr;
	down->addr.sin_port = htons(pServer->getPort());
	down->head.UID = ServerUID;
	pServer->removePeer(user._uid);
	cout << "user: " << user._uid << " removed" << endl;
	map_userinfo.erase(user._uid);

	if (pServer->isEmpty()) {										// ������û���˾�����
		cout << "destroy class" << endl;
		if (isClassExist(classid)) {
			destroyClass(classid);
		}
	}
	WriteOut(inputMsg);
}

DWORD CAgentServer::MsgHandler(TS_PEER_MESSAGE& inputMsg) {		// ���տ��������󣬼����˳��༶�ȵ�
	enum PacketType type = getType(inputMsg.msg);

	switch (type) {
	case ENTERCLASS:
		{
			UP_AGENTSERVICE* in = (UP_AGENTSERVICE*) &inputMsg.msg;		// �յ�����/�˳��༶������
			UserBase user;
			user._classid = in->classid;
			user._reserved = in->head.reserved;
			user._role = in->role;
			user._uid = in->head.UID;

			memcpy(user._username, in->username, 20);
			memcpy(user._password, in->password, 20);
			
			enterClass(inputMsg, user);							// �������༶���󣬲��ظ�
			break;
		}
	case LEAVECLASS:
		{
			UP_AGENTSERVICE* in = (UP_AGENTSERVICE*) &inputMsg.msg;		// �յ�����/�˳��༶������
			UserBase user;
			user._classid = in->classid;
			user._reserved = in->head.reserved;
			user._role = in->role;
			user._uid = in->head.UID;

			memcpy(user._username, in->username, 20);
			memcpy(user._password, in->password, 20);

			leaveClass(inputMsg, user);							// �����˳��༶���󣬲��ظ�
			break;
		}
	case HEARTBEAT:
		{
			UP_HEARTBEAT* in = (UP_HEARTBEAT*) &inputMsg.msg;
			TS_UINT64 uid = in->head.UID;

			iop_lock(&lockOfflineMaps);
			if (heartBeatTime.count(uid) == 0)					// ������ʱ�����set��
				return 0;
			heartBeatTime[uid] = in->head.time;

			if (offlineUsers.count(uid) > 0)					// ���������Ѿ������û�
				offlineUsers.erase(uid);						// ����ȡ������״̬
			iop_unlock(&lockOfflineMaps);
			cout << "received heart beat" << endl;
			break;
		}
	default:
		break;
	}

	return 0;
}

int CAgentServer::getOfflineUsers(set<TS_UINT64>& out) {
	out.insert(offlineUsers.begin(), offlineUsers.end());
	return offlineUsers.size();
}


void* scanOfflineProc(LPVOID lpParam) {
	pthread_detach(pthread_self());
	CAgentServer* object = (CAgentServer*) lpParam;
	if (!object) {
		return 0;
	}
	while (true) {
		object->scanOffline();
		iop_usleep(HeartBeatInterval);
	}
	return 0;
}
