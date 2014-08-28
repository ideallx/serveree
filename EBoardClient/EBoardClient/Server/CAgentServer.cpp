#include "CAgentServer.h"

#include "CWSServer.h"

#include <iostream>
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

bool CAgentServer::isClassExist(int classid) {
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

void CAgentServer::createClass(int classid) {
	bool flag = false;
	iop_lock(&lockWorkServer);
	if (isClassExist(classid)) {
		flag = true;
	}

	if (!flag) {
		iop_lock(&lockPortqueue);
		int port = port_queue.front();
		port_queue.pop();
		iop_unlock(&lockPortqueue);

		CWSServer* pWorker = new CWSServer(port, 1);
		map_workserver[classid] = pWorker;
		pWorker->Start(port);

		cout << "Worker Server Start successfully on Port "<< port << "." << endl;
	}
	iop_unlock(&lockWorkServer);
}

void CAgentServer::destroyClass(int classid) {
	iop_lock(&lockWorkServer);
	if (isClassExist(classid)) {
		CWSServer* pServer = map_workserver[classid];
		int port = pServer->getPort();
		pServer->Stop();
		cout << "Worker Server Stop successfully on Port "<< port << "." << endl;
		delete pServer;
		map_workserver[classid] = NULL;
		map_workserver.erase(classid);
		
		iop_lock(&lockPortqueue);
		port_queue.push(port);
		iop_unlock(&lockPortqueue);
	}
	iop_unlock(&lockWorkServer);
}

bool CAgentServer::enterClass(sockaddr_in addr, UserBase user) {
	createClass(user._classid);
	
	iop_lock(&lockWorkServer);
	CWSServer* pServer = map_workserver[user._classid];
	bool ret = pServer->addPeer(addr, user._uid);
	iop_unlock(&lockWorkServer);
	return ret;
}

void CAgentServer::leaveClass(int classid, int uid) {
	bool ret = false;
	
	iop_lock(&lockWorkServer);
	CWSServer* pServer = map_workserver[classid];
	if (pServer != NULL) {
		pServer->removeUser(uid);
		ret = pServer->isEmpty();
	}
	iop_unlock(&lockWorkServer);

	if (ret) {
		cout << "destroy class" << endl;
		destroyClass(classid);
	}
}

DWORD CAgentServer::MsgHandler(TS_PEER_MESSAGE& pmsg) {
	return 0;
}