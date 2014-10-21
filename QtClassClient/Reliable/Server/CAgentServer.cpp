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
	delete pServer;

	cout << "Worker Server Stop successfully on Port " << port << "." << endl;
	map_workserver[classid] = NULL;
	map_workserver.erase(classid);
		
	iop_lock(&lockPortqueue);
	port_queue.push(port);				// 返还给端口队列
	iop_unlock(&lockPortqueue);

	iop_unlock(&lockWorkServer);
}

void CAgentServer::scanOffline() {
	TS_UINT64 currentTime = getServerTime();
	
	if (heartBeatTime.size() == 0)
		return;

	iop_lock(&lockOfflineMaps);
	int maxAllowedInterval = HeartBeatInterval * 3;
	for (auto iter = heartBeatTime.begin(); iter != heartBeatTime.end(); ) {
		cout << iter->first << " lost " << currentTime - iter->second << endl;
		if (currentTime - iter->second > maxAllowedInterval) {
			TS_PEER_MESSAGE msg;  
			userLogoutNotify(msg, iter->first);
			
			CWSServer* pServer = map_workserver[map_userinfo[iter->first]._classid];
			if (pServer != NULL) {
				pServer->removeUser(iter->first);
			}

			cout << iter->first << "drop connection" << endl;
			offlineUsers.insert(iter->first);
			heartBeatTime.erase(iter++);
		} else {
			iter++;
		}
	}
	iop_unlock(&lockOfflineMaps);
}

bool CAgentServer::enterClass(TS_PEER_MESSAGE& inputMsg, UserBase user) {
	if (!isClassExist(user._classid)) {								// 第一个用户加入，则创建班级
		createClass(user._classid);
	}
	
	iop_lock(&lockWorkServer);
	CWSServer* pServer = map_workserver[user._classid];
    if (NULL == pServer)
        return false;
	pServer->addPeer(inputMsg.peeraddr, user._uid);					// 这里的地址是client agent的端口地址
	iop_unlock(&lockWorkServer);


	DOWN_AGENTSERVICE* down = (DOWN_AGENTSERVICE*) &inputMsg.msg;	// 进入班级成功，把服务器信息告诉客户端
	down->result = SuccessEnterClass;
	down->addr = *pServer->getServerAddr();							// server的地址加入到报文中

	down->head.time = getServerTime();
	down->head.UID = ServerUID;
	down->head.size = sizeof(DOWN_AGENTSERVICE);
	WriteOut(inputMsg);

	cout << "Add User: " << user._uid << "into class" << user._classid << endl; 
	map_userinfo.insert(make_pair(user._uid, user));
	heartBeatTime.insert(make_pair(user._uid, down->head.time));

	userLoginNotify(inputMsg, user._uid);

	pServer->sendPrevMessage(user._uid);
	return true;
}

void CAgentServer::sendLeaveSuccess(TS_PEER_MESSAGE& pmsg) {
	DOWN_AGENTSERVICE* down = (DOWN_AGENTSERVICE*) &pmsg.msg;	// 退出班级成功，把服务器信息告诉客户端
	down->result = SuccessLeaveClass;
	down->addr = pmsg.peeraddr;
	down->head.UID = ServerUID;
	down->head.size = sizeof(DOWN_AGENTSERVICE);
	WriteOut(pmsg);
}

void CAgentServer::leaveClass(TS_PEER_MESSAGE& inputMsg, UserBase user) {
	iop_lock(&lockWorkServer);
	if (map_userinfo.count(user._uid) == 0) {						// if no user
		sendLeaveSuccess(inputMsg);
		return;
	}

	TS_UINT64 classid = user._classid;
	CWSServer* pServer = map_workserver[classid];
    if (NULL == pServer) 											// server端删除这个用户
        return;

    pServer->removeUser(user._uid);
	iop_unlock(&lockWorkServer);

	sendLeaveSuccess(inputMsg);
	userLogoutNotify(inputMsg, user._uid);
	pServer->removePeer(user._uid);
	cout << "user: " << user._uid << " removed" << endl;
	map_userinfo.erase(user._uid);

	if (pServer->isEmpty()) {										// 教室里没人了就销毁
		cout << "destroy class" << endl;
		if (isClassExist(classid)) {
			destroyClass(classid);
		}
	}
}

void CAgentServer::userLoginNotify(TS_PEER_MESSAGE& pmsg, TS_UINT64 uid) {
    CWSServer* pServer = getServerByUID(uid);
    if (NULL == pServer) {
		return;
	}

	map<TS_UINT64, CPeerConnection*>* allUsers = pServer->getPeers();
	for (auto iter = allUsers->begin(); iter != allUsers->end(); iter++) {
		if (iter->first != uid && iter->first != ServerUID) {		// 所有人收到新增用户信息
			SERVER_CLASS_ADD_USER *down = (SERVER_CLASS_ADD_USER*) &pmsg.msg;
			UserBase us = map_userinfo[uid];
			down->enterUser.uid = uid;
			down->enterUser.reserved = us._reserved;
			down->enterUser.classid = us._classid;
			down->enterUser.role = us._role;
			memcpy(down->enterUser.username, us._username, 20);

			down->head.UID = ServerUID;
			down->head.sequence = 0;
			down->head.type = ADDUSER;
			down->head.size = sizeof(SERVER_CLASS_ADD_USER);
			iter->second->send(pmsg.msg.Body, sizeof(SERVER_CLASS_ADD_USER));
		} else {													// 新用户收到现有用户列表
			SERVER_CLASS_USER_LIST *down = (SERVER_CLASS_USER_LIST*) &pmsg.msg;
			int calc = 0;
			for (auto iter2 = allUsers->begin(); iter2 != allUsers->end(); iter2++) {
				if (iter2->first == uid)
					continue;

				if (calc == 10)
					iter->second->send(pmsg.msg.Body, sizeof(SERVER_CLASS_USER_LIST));
					
				USER_INFO ui;
				UserBase us = map_userinfo[iter2->first];
				ui.uid = us._uid;
				ui.classid = us._classid;
				ui.reserved = us._reserved;
				ui.role = us._role;
				memcpy(ui.username, us._username, 20);

				down->users[calc] = ui;
				down->userNumberInMessage = ++calc;
				down->head.type = USERLIST;
				down->head.UID = ServerUID;
				down->head.sequence = 0;
				down->head.size = sizeof(SERVER_CLASS_USER_LIST);
			}
			if (calc != 0) {
				iter->second->send(pmsg.msg.Body, sizeof(SERVER_CLASS_USER_LIST));
			}
		}
	}
}


void CAgentServer::userLogoutNotify(TS_PEER_MESSAGE& pmsg, TS_UINT64 uid) {
	if (map_userinfo.count(uid) == 0) {
		return;
	}

	CWSServer* pServer = map_workserver[map_userinfo[uid]._classid];
	if (pServer == NULL) {
		return;
	}
	
	map<TS_UINT64, CPeerConnection*>* allUsers = pServer->getPeers();
	for (auto iter = allUsers->begin(); iter != allUsers->end(); iter++) {
		if (iter->first != uid && iter->first != ServerUID) {
			SERVER_CLASS_REMOVE_USER *down = (SERVER_CLASS_REMOVE_USER*) &pmsg.msg;
			down->leaveUser = uid;
			down->head.type = REMOVEUSER;
			down->head.UID = ServerUID;
			down->head.sequence = 0;
			down->head.size = sizeof(SERVER_CLASS_REMOVE_USER);
			iter->second->send(pmsg.msg.Body, sizeof(SERVER_CLASS_REMOVE_USER));
		}
	}
}

DWORD CAgentServer::MsgHandler(TS_PEER_MESSAGE& inputMsg) {		// 接收控制类请求，加入退出班级等等
	enum PacketType type = getType(inputMsg.msg);

	switch (type) {
	case ENTERCLASS:
		{
			UP_AGENTSERVICE* in = (UP_AGENTSERVICE*) &inputMsg.msg;		// 收到进入/退出班级的请求
			UserBase user;
			user._classid = in->classid;
			user._reserved = in->head.reserved;
			user._role = in->role;
			user._uid = in->head.UID;

			memcpy(user._username, in->username, 20);
			memcpy(user._password, in->password, 20);
			
			enterClass(inputMsg, user);									// 处理进入班级请求，并回复
			break;
		}
	case LEAVECLASS:
		{
			UP_AGENTSERVICE* in = (UP_AGENTSERVICE*) &inputMsg.msg;		// 收到进入/退出班级的请求
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
	case HEARTBEAT:
		{
			UP_HEARTBEAT* in = (UP_HEARTBEAT*) &inputMsg.msg;
			TS_UINT64 uid = in->head.UID;

			if (heartBeatTime.count(uid) == 0)					// 将最新时间加入set中
				return 0;
			iop_lock(&lockOfflineMaps);
			heartBeatTime[uid] = in->head.time;

			if (offlineUsers.count(uid) > 0)					// 如果这个是已经掉线用户
				offlineUsers.erase(uid);						// 现在取消掉线状态
			iop_unlock(&lockOfflineMaps);
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

bool CAgentServer::Start(unsigned short port) {
	if (CServer::Start(port) == false)
		return false;
	pthread_t p;
	int rc = pthread_create(&p, NULL, scanOfflineProc, (void*) this);
	if (0 == rc) {
		iop_usleep(10);
		cout << "Scan OffLine Thread start successfully " << endl;
	} else {
		turnOff();
	}
}

CWSServer* CAgentServer::getServerByUID(TS_UINT64 uid) {
    if (map_userinfo.count(uid) == 0) {
        return NULL;
    }

    return map_workserver[map_userinfo[uid]._classid];
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
