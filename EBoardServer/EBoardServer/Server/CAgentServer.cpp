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

	iop_lock(&lockPortqueue);				// 获取一个未用过的端口号
	int port = port_queue.front();
	port_queue.pop();
	iop_unlock(&lockPortqueue);

	CWSServer* pWorker = new CWSServer(classid, 1);		// 创建一个新的WorkServer
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
	int port = pServer->getPort();		// 获取服务器端口
	pServer->Stop();
	cout << "Worker Server Stop successfully on Port " << port << "." << endl;
	delete pServer;
	map_workserver[classid] = NULL;
	map_workserver.erase(classid);
		
	iop_lock(&lockPortqueue);
	port_queue.push(port);				// 返还给端口队列
	iop_unlock(&lockPortqueue);

	iop_unlock(&lockWorkServer);
}

bool CAgentServer::enterClass(TS_PEER_MESSAGE& inputMsg, UserBase user) {
	if (!isClassExist(user._classid)) {								// 第一个用户加入，则创建班级
		createClass(user._classid);
	}
	
	iop_lock(&lockWorkServer);
	CWSServer* pServer = map_workserver[user._classid];
	// pServer->addPeer(inputMsg.peeraddr, user._uid);				// 这里的地址是client agent的端口地址
	iop_unlock(&lockWorkServer);

	DOWN_AGENTSERVICE* down = (DOWN_AGENTSERVICE*) &inputMsg.msg;	// 进入班级成功，把服务器信息告诉客户端
	down->result = Success;
	down->addr = *pServer->getServerAddr();							// server的地址加入到报文中
	WriteOut(inputMsg);
	return true;
}

void CAgentServer::leaveClass(TS_PEER_MESSAGE& inputMsg, UserBase user) {
	iop_lock(&lockWorkServer);
	TS_UINT64 classid = user._classid;
	CWSServer* pServer = map_workserver[classid];
	if (pServer != NULL) {											// server端删除这个用户
		pServer->removeUser(user._uid);
	}
	iop_unlock(&lockWorkServer);

	DOWN_AGENTSERVICE* down = (DOWN_AGENTSERVICE*) &inputMsg.msg;	// 退出班级成功，把服务器信息告诉客户端
	down->result = Success;
	down->addr = inputMsg.peeraddr;
	down->addr.sin_port = htons(pServer->getPort());
	WriteOut(inputMsg);
	pServer->removePeer(user._uid);
	cout << "user: " << user._uid << " removed" << endl;

	if (pServer->isEmpty()) {										// 教室里没人了就销毁
		cout << "destroy class" << endl;
		if (isClassExist(classid)) {
			destroyClass(classid);
		}
	}

}

DWORD CAgentServer::MsgHandler(TS_PEER_MESSAGE& inputMsg) {		// 接收控制类请求，加入退出班级等等
	enum PackageType type = getType(inputMsg.msg);
	UP_AGENTSERVICE* in = (UP_AGENTSERVICE*) &inputMsg.msg;		// 收到进入/退出班级的请求

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
			
			enterClass(inputMsg, user);							// 处理进入班级请求，并回复
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

			leaveClass(inputMsg, user);							// 处理退出班级请求，并回复
			break;
		}
	default:
		break;
	}

	return 0;
}