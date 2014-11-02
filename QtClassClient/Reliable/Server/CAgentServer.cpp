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
    Sleep(100);
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
		map_userinfo.insert(make_pair(user._uid, user));
		map_alluser.insert(make_pair(string((char*) user._username), user._uid));
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
#ifdef _DEBUG_INFO_
	cout << "Worker Server Start successfully on Port " << port << "." << endl;
#endif
	iop_unlock(&lockWorkServer);
}

void CAgentServer::destroyClass(TS_UINT64 classid) {
	iop_lock(&lockWorkServer);

	CWSServer* pServer = map_workserver[classid];
	if (NULL == pServer)
		return;

	int port = pServer->getPort();		// ��ȡ�������˿�
	delete pServer;

#ifdef _DEBUG_INFO_
	cout << "Worker Server Stop successfully on Port " << port << "." << endl;
#endif
	map_workserver[classid] = NULL;
	map_workserver.erase(classid);
		
	iop_lock(&lockPortqueue);
	port_queue.push(port);				// �������˿ڶ���
	iop_unlock(&lockPortqueue);

	iop_unlock(&lockWorkServer);
}

void CAgentServer::scanOffline() {
    while (isRunning()) {

        TS_UINT64 currentTime = getServerTime();

        if (heartBeatTime.size() == 0)
            continue;

        iop_lock(&lockOfflineMaps);
        int maxAllowedInterval = HeartBeatInterval * 3;
        for (auto iter = heartBeatTime.begin(); iter != heartBeatTime.end(); ) {
#ifdef _DEBUG_INFO_
            cout << iter->first << " lost " << currentTime - iter->second << endl;
#endif
            if (currentTime - iter->second > maxAllowedInterval) {
                TS_PEER_MESSAGE msg;
                userLogoutNotify(msg, iter->first);

                CWSServer* pServer = map_workserver[map_userinfo[iter->first]._classid];
                if (pServer != NULL) {
                    pServer->removeUser(iter->first);
                }
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

        iop_usleep(HeartBeatInterval);
    }
}

bool CAgentServer::enterClass(TS_PEER_MESSAGE& inputMsg, UserBase user) {
	if (!isClassExist(user._classid)) {								// ��һ���û����룬�򴴽��༶
		createClass(user._classid);
	}
	
	enum MsgResult result = ErrorUnknown;
	iop_lock(&lockWorkServer);	
	CWSServer* pServer = map_workserver[user._classid];
    if (NULL == pServer)
        return false;
	iop_unlock(&lockWorkServer);

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

	DOWN_AGENTSERVICE* down = (DOWN_AGENTSERVICE*) &inputMsg.msg;	// ����༶�ɹ����ѷ�������Ϣ���߿ͻ���
	down->result = result;
	down->addr = *pServer->getServerAddr();							// server�ĵ�ַ���뵽������
	down->uid = user._uid;
    down->role = (enum RoleOfClass) user._role;

	down->head.time = getServerTime();
	down->head.UID = ServerUID;
	down->head.size = sizeof(DOWN_AGENTSERVICE);
	WriteOut(inputMsg);

#ifdef _DEBUG_INFO_
	cout << "Add User: " << user._uid << "into class" << user._classid << endl; 
#endif
	if (SuccessEnterClass == result) {
		pServer->addPeer(inputMsg.peeraddr, user._uid);					// ����ĵ�ַ��client agent�Ķ˿ڵ�ַ
		heartBeatTime.insert(make_pair(user._uid, down->head.time));
		userLoginNotify(inputMsg, user._uid);
		pServer->sendPrevMessage(user._uid);
	}
	return true;
}

void CAgentServer::sendLeaveSuccess(TS_PEER_MESSAGE& pmsg) {
	DOWN_AGENTSERVICE* down = (DOWN_AGENTSERVICE*) &pmsg.msg;	// �˳��༶�ɹ����ѷ�������Ϣ���߿ͻ���
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
    if (NULL == pServer) 											// server��ɾ������û�
        return;

    pServer->removeUser(user._uid);

	sendLeaveSuccess(inputMsg);
	userLogoutNotify(inputMsg, user._uid);
	iop_unlock(&lockWorkServer);

#ifdef _DEBUG_INFO_
	cout << "user: " << user._uid << " removed" << endl;
#endif

	if (pServer->isEmpty()) {										// ������û���˾�����
#ifdef _DEBUG_INFO_
		cout << "destroy class" << endl;
#endif
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
		if (iter->first != uid && iter->first != ServerUID) {		// �������յ������û���Ϣ
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
		} else {													// ���û��յ������û��б�
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

DWORD CAgentServer::MsgHandler(TS_PEER_MESSAGE& inputMsg) {		// ���տ��������󣬼����˳��༶�ȵ�
	enum PacketType type = getType(inputMsg.msg);
	
	switch (type) {
	case ENTERCLASS:
		{
			UP_AGENTSERVICE* in = (UP_AGENTSERVICE*) &inputMsg.msg;		// �յ�����/�˳��༶������
			UserBase user;
			user._classid = in->classid;
            user._reserved = in->head.reserved;
			user._uid = in->head.UID;

			memcpy(user._username, in->username, 20);
			memcpy(user._password, in->password, 20);
			
			enterClass(inputMsg, user);									// �������༶���󣬲��ظ�
			break;
		}
	case LEAVECLASS:
		{
			UP_AGENTSERVICE* in = (UP_AGENTSERVICE*) &inputMsg.msg;		// �յ�����/�˳��༶������
			UserBase user;
			user._classid = in->classid;
            user._reserved = in->head.reserved;
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

			if (heartBeatTime.count(uid) == 0)					// ������ʱ�����set��
				return 0;
			iop_lock(&lockOfflineMaps);
			heartBeatTime[uid] = in->head.time;

			if (offlineUsers.count(uid) > 0)					// ���������Ѿ������û�
				offlineUsers.erase(uid);						// ����ȡ������״̬
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
