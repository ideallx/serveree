#include <iostream>
#include <string>

#include "CAgentServer.h"
#include "CWSServer.h"

using namespace std;

CAgentServer::CAgentServer() {
	iop_lock_init(&lockWorkServer);
	iop_lock_init(&lockPortqueue);
	
	iop_lock(&lockPortqueue);
	for(int i = 10000; i < 20000; i++){
		port_queue.push(i);
	}
	iop_unlock(&lockPortqueue);
}

CAgentServer::~CAgentServer() {
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

	iop_lock(&lockPortqueue);
	int port = port_queue.front();
	port_queue.pop();
	iop_unlock(&lockPortqueue);

	CWSServer* pWorker = new CWSServer(port, 1);
	map_workserver[classid] = pWorker;
	pWorker->Start(port);

	cout << "Worker Server Start successfully on Port " << port << "." << endl;
	iop_unlock(&lockWorkServer);
}

void CAgentServer::destroyClass(TS_UINT64 classid) {
	iop_lock(&lockWorkServer);

	CWSServer* pServer = map_workserver[classid];
	int port = pServer->getPort();
	pServer->Stop();
	cout << "Worker Server Stop successfully on Port " << port << "." << endl;
	delete pServer;
	map_workserver[classid] = NULL;
	map_workserver.erase(classid);
		
	iop_lock(&lockPortqueue);
	port_queue.push(port);
	iop_unlock(&lockPortqueue);

	iop_unlock(&lockWorkServer);
}

bool CAgentServer::enterClass(TS_PEER_MESSAGE& inputMsg, UserBase user) {
	if (!isClassExist(user._classid)) {
		createClass(user._classid);
	}
	
	iop_lock(&lockWorkServer);
	CWSServer* pServer = map_workserver[user._classid];
	// bool ret = pServer->addPeer(inputMsg.peeraddr, user._uid);
	iop_unlock(&lockWorkServer);

	DOWN_AGENTSERVICE* down = (DOWN_AGENTSERVICE*) &inputMsg.msg;	// 进入班级成功，吧服务器信息告诉客户端
	down->result = Success;
	down->addr = inputMsg.peeraddr;
	down->addr.sin_port = htons(user._classid);
	WriteOut(inputMsg);

	return true;
}

void CAgentServer::leaveClass(TS_UINT64 classid, TS_UINT64 uid) {
	iop_lock(&lockWorkServer);
	CWSServer* pServer = map_workserver[classid];
	if (pServer != NULL) {
		pServer->removeUser(uid);
	}
	iop_unlock(&lockWorkServer);

	if (pServer->isEmpty()) {			// 没人在教室了就销毁
		cout << "destroy class" << endl;
		if (isClassExist(classid)) {
			destroyClass(classid);
		}
	}
}

DWORD CAgentServer::MsgHandler(TS_PEER_MESSAGE& inputMsg) {		// 接收控制类请求，加入退出班级等等
	enum PackageType type = getType(inputMsg.msg);
	UP_AGENTSERVICE* in = (UP_AGENTSERVICE*) &inputMsg.msg;

	switch (type) {
	case ENTERCLASS:
		{
			UserBase user;
			user._classid = in->classid;
			user._reserved = in->head.reserved;
			user._role = in->role;
			user._uid = in->head.UID;

			memcpy(user._username, in->username, 20);
			memcpy(user._password, in->password, 20);
			
			enterClass(inputMsg, user);
			break;
		}
	case LEAVECLASS:
		{
			UserBase user;
			user._classid = in->classid;
			user._reserved = in->head.reserved;
			user._role = in->role;
			user._uid = in->head.UID;

			memcpy(user._username, in->username, 20);
			memcpy(user._password, in->password, 20);

			leaveClass(in->classid, in->head.UID);
			break;
		}
	default:
		break;
	}

	return 0;
}