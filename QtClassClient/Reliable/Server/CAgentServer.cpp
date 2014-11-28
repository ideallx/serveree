#include <iostream>
#include "CAgentServer.h"
#include "CWSServer.h"
#include "../DataUnit/UserBase.h"

using namespace std;

thread_ret_type thread_func_call scanOfflineProc(LPVOID lpParam) {
    iop_thread_detach_self();
    CAgentServer* object = (CAgentServer*) lpParam;
    if (!object) {
        iop_thread_exit(0);
        return 0;
    }
    object->scanOffline();
#ifdef _DEBUG_INFO_
    cout << "scanOfflineProc exit" << endl;
#endif
    iop_thread_exit(0);
    return 0;
}


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
	Stop();
	iop_lock_destroy(&lockOfflineMaps);
	iop_lock_destroy(&lockWorkServer);
	iop_lock_destroy(&lockPortqueue);
    iop_thread_cancel(pthread_scanoffline);

	for (auto iter = map_workserver.begin(); iter != map_workserver.end(); ) {
		delete iter->second;
		map_workserver.erase(iter++);
	}
    iop_usleep(100);
}

bool CAgentServer::isClassExist(TS_UINT64 classid) {
	return (map_workserver.count(classid) > 0) && 
		(map_workserver[classid] != NULL);
}

void CAgentServer::loadUser() {
	FILE* fp = freopen("User.txt", "r", stdin);
    if (fp == NULL) {
        cout << "cant get user list" << endl;
        return;
    }
	UserBase user;
	int cnt = 0;
	cin >> cnt;
	while (cnt-- > 0) {
		user._reserved = 0;
		cin >> user._username >> user._password >> user._uid 
			>> user._classid  >> user._role;
		user._role -= '0';
		map_userinfo.insert(make_pair(user._uid, user));
		map_alluser.insert(make_pair(string((char*) user._username), user._uid));
	}
	fclose(stdin);
}

void CAgentServer::createClass(TS_UINT64 classid) {
	iop_lock(&lockPortqueue);				// 获取一个未用过的端口号
	int port = port_queue.front();
	port_queue.pop();
	iop_unlock(&lockPortqueue);
	
	CWSServer* pWorker = new CWSServer(classid, 1);		// 创建一个新的WorkServer
	map_workserver[classid] = pWorker;
	if (!pWorker->Start(port))
		return;
#ifdef _DEBUG_INFO_
	cout << "Worker Server Start successfully on Port " << port << "." << endl;
#endif
}

void CAgentServer::destroyClass(TS_UINT64 classid) {
	CWSServer* pServer = map_workserver[classid];
	if (NULL == pServer)
		return;

	int port = pServer->getPort();		// 获取服务器端口
	delete pServer;

#ifdef _DEBUG_INFO_
	cout << "Worker Server Stop successfully on Port " << port << "." << endl;
#endif
	map_workserver[classid] = NULL;
	map_workserver.erase(classid);
		
	iop_lock(&lockPortqueue);
	port_queue.push(port);				// 返还给端口队列
	iop_unlock(&lockPortqueue);
}

void CAgentServer::scanOffline() {
    while (isRunning()) {
        iop_usleep(HeartBeatInterval);

        TS_UINT64 currentTime = getServerTime();

        if (heartBeatTime.size() == 0)
            continue;

        iop_lock(&lockOfflineMaps);
        int maxAllowedInterval = HeartBeatInterval * 3;
        for (auto iter = heartBeatTime.begin(); iter != heartBeatTime.end(); ) {
#ifdef _DEBUG_INFO_
            cout << iter->first << " lost " << currentTime - iter->second << endl;
#endif
			// TODO iter->second may be a little bigger than currentTime
            if (currentTime - iter->second > maxAllowedInterval) {
                TS_PEER_MESSAGE msg;

                CWSServer* pServer = map_workserver[map_userinfo[iter->first]._classid];
                if (pServer != NULL) {
                    pServer->removeUser(iter->first);
                }
                userLogoutNotify(msg, iter->first);
#ifdef _DEBUG_INFO_
                cout << iter->first << "drop connection" << endl;
#endif
                offlineUsers.insert(iter->first);
                heartBeatTime.erase(iter++);
            } else {
                iter++;
            }
        }
        iop_unlock(&lockOfflineMaps);

		// TODO iterator
		auto iter = map_workserver.begin();
		if (iter == map_workserver.end() || iter->second == NULL)
			continue;
        iter->second->sendMaxSeqList();

        TS_PEER_MESSAGE pmsg;
        sendUserList(pmsg, iter->second);

    }
}

bool CAgentServer::enterClass(TS_PEER_MESSAGE& inputMsg, UserBase user) {
	enum MsgResult result = ErrorUnknown;
	// find user in usermap by username, then check password
	auto findUser = map_alluser.find(string((char*) user._username));
	if (findUser == map_alluser.end()) {
		result = ErrorUsername;
	} else if (strcmp((char*) map_userinfo[findUser->second]._password, (char*) user._password) != 0) {
		result = ErrorPassword;
	} else {
		user._uid = findUser->second;
        user._role = map_userinfo[findUser->second]._role;
		result = SuccessEnterClass;
	}

	iop_lock(&lockWorkServer);
	if (!isClassExist(user._classid)) {								// 第一个用户加入，则创建班级
		createClass(user._classid);
	}

	CWSServer* pServer = map_workserver[user._classid];
    if (NULL == pServer)
        return false;

	auto loginUsers = pServer->getPeers();
	iop_unlock(&lockWorkServer);

	if (loginUsers->find(user._uid) != loginUsers->end()) {					// 登陆过，推掉原来的
		sockaddr_in backup = inputMsg.peeraddr;
		inputMsg.peeraddr = *loginUsers->at(user._uid)->getPeer();
		if (memcmp(&backup, &inputMsg.peeraddr, sizeof(sockaddr_in))) {		// 同一客户端重复登录则不管
			sendLeaveSuccess(inputMsg);
			inputMsg.peeraddr = backup;
		}
	}

	
	DOWN_AGENTSERVICE* down = (DOWN_AGENTSERVICE*) &inputMsg.msg;	// 进入班级成功，把服务器信息告诉客户端
	down->result = result;
	down->addr = *pServer->getServerAddr();							// server的地址加入到报文中
	down->uid = user._uid;
    down->role = (enum RoleOfClass) user._role;

	down->head.time = getServerTime();
	down->head.UID = ServerUID;
	down->head.size = sizeof(DOWN_AGENTSERVICE);
	down->head.sequence = 0;
	down->lastSeq = pServer->getMaxSeqOfUID(down->uid);
	WriteOut(inputMsg);
	
#ifdef _DEBUG_INFO_
	cout << "Add User: " << user._uid << "into class" << user._classid << endl; 
#endif
	if (SuccessEnterClass == result) {
		iop_lock(&lockWorkServer);
		pServer->addPeer(inputMsg.peeraddr, user._uid);					// 这里的地址是client agent的端口地址
		if (heartBeatTime.count(user._uid) == 0)
			heartBeatTime.insert(make_pair(user._uid, getServerTime()));
		else
			heartBeatTime[user._uid] = getServerTime();
		userLoginNotify(inputMsg, user._uid);
        // pServer->sendPrevMessage(user._uid);
		iop_unlock(&lockWorkServer);
	}


	pServer->sendMaxSeqList();
	return true;
}

void CAgentServer::sendLeaveSuccess(TS_PEER_MESSAGE& pmsg) {
	DOWN_AGENTSERVICE* down = (DOWN_AGENTSERVICE*) &pmsg.msg;	// 退出班级成功，把服务器信息告诉客户端
	down->result = SuccessLeaveClass;
	down->addr = pmsg.peeraddr;
	down->head.UID = ServerUID;
	down->head.size = sizeof(DOWN_AGENTSERVICE);
	down->head.sequence = 0;
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
    if (NULL == pServer) {											// server端删除这个用户
		sendLeaveSuccess(inputMsg);
        return;
	}


	sendLeaveSuccess(inputMsg);
	userLogoutNotify(inputMsg, user._uid);
    pServer->removeUser(user._uid);
	heartBeatTime.erase(user._uid);

	iop_unlock(&lockWorkServer);

#ifdef _DEBUG_INFO_
	cout << "user: " << user._uid << " removed" << endl;
#endif

	if (pServer->isEmpty()) {										// 教室里没人了就销毁
#ifdef _DEBUG_INFO_
		cout << "destroy class" << endl;
#endif
		//if (isClassExist(classid)) {
		//	destroyClass(classid);
		//}
	}
}

void CAgentServer::userLoginNotify(TS_PEER_MESSAGE& pmsg, TS_UINT64 uid) {
    CWSServer* pServer = getServerByUID(uid);
    if (NULL == pServer) {
		return;
	}

	map<TS_UINT64, CPeerConnection*>* loginUser = pServer->getPeers();
	for (auto iter = loginUser->begin(); iter != loginUser->end(); iter++) {
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
			
			pmsg.peeraddr = *iter->second->getPeer();
			WriteOut(pmsg);
        }
	}
    sendUserList(pmsg, pServer);
}

void CAgentServer::sendUserList(TS_PEER_MESSAGE& pmsg, CWSServer* pServer) {
    if (NULL == pServer) {
        return;
    }

    map<TS_UINT64, CPeerConnection*>* loginUser = pServer->getPeers();
    SERVER_CLASS_USER_LIST *down = (SERVER_CLASS_USER_LIST*) &pmsg.msg;

    int calc = 0;
    for (auto iter2 = map_alluser.begin(); iter2 != map_alluser.end(); iter2++) {
        if (calc == 10) {
            for (auto sendList = loginUser->begin(); sendList != loginUser->end(); sendList++) {
                pmsg.peeraddr = *sendList->second->getPeer();
                WriteOut(pmsg);
                calc = 0;
            }
        }

        USER_INFO ui;
        UserBase us = map_userinfo[iter2->second];
        ui.uid = us._uid;
        ui.classid = us._classid;
        ui.reserved = us._reserved;
        ui.role = us._role;
        if (loginUser->find(iter2->second) == loginUser->end()) {
            ui.isLoggedIn = false;
        } else {
            ui.isLoggedIn = true;
        }
        memcpy(ui.username, us._username, 20);

        down->users[calc] = ui;
        down->userNumberInMessage = ++calc;

        down->head.type = USERLIST;
        down->head.UID = ServerUID;
        down->head.sequence = 0;
        down->head.size = sizeof(SERVER_CLASS_USER_LIST);
    }
    if (calc != 0) {
        for (auto sendList = loginUser->begin(); sendList != loginUser->end(); sendList++) {
            pmsg.peeraddr = *sendList->second->getPeer();
            WriteOut(pmsg);
            calc = 0;
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

			if (map_userinfo.find(uid) == map_userinfo.end())
				break;

			if (heartBeatTime.count(uid) == 0) {				// 将最新时间加入set中
				//CWSServer* pServer = getServerByUID(uid);
				//if (pServer == NULL) {
				//	createClass(map_userinfo.find(uid)->second._classid);
				//	pServer = getServerByUID(uid);
				//}
				//pServer->addPeer(inputMsg.peeraddr, in->head.UID);					// 这里的地址是client agent的端口地址
				//heartBeatTime.insert(make_pair(uid, in->head.time));
				break;
			}

			iop_lock(&lockOfflineMaps);
			heartBeatTime[uid] = in->head.time;

			if (offlineUsers.count(uid) > 0)					// 如果这个是已经掉线用户
				offlineUsers.erase(uid);						// 现在取消掉线状态

			iop_unlock(&lockOfflineMaps);
			break;
		}
	case SCANPORT:
		{
			TS_MESSAGE_HEAD* head = (TS_MESSAGE_HEAD*) &inputMsg.msg;
			head->UID = 0;
			head->sequence = 0;
			head->subSeq = 0;
			WriteOut(inputMsg);
		}
		break;
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
    int rc = iop_thread_create(&pthread_scanoffline, scanOfflineProc, (void *) this, 0);
	if (0 == rc) {
		iop_usleep(10);
#ifdef _DEBUG_INFO_
		cout << "Scan OffLine Thread start successfully " << endl;
#endif
	} else {
		turnOff();
	}
	loadUser();
	return isStarted;
}

CWSServer* CAgentServer::getServerByUID(TS_UINT64 uid) {
    if (map_userinfo.count(uid) == 0) {
        return NULL;
    }

    return map_workserver[map_userinfo[uid]._classid];
}
