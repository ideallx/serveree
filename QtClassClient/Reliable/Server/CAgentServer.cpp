#include <iostream>
#include "CAgentServer.h"
#include "CWSServer.h"
#include "../DataUnit/UserBase.h"

using namespace std;

thread_ret_type thread_func_call scanOfflineProc(LPVOID lpParam) {
    iop_thread_detach_self();
    CAgentServer* object = reinterpret_cast<CAgentServer*> (lpParam);
    if (!object) {
        iop_thread_exit(0);
        return 0;
    }
    object->scanAgent();
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
	iop_lock(&lockWorkServer);
	bool isTrue = (map_workserver.count(classid) > 0) && 
		(map_workserver[classid] != NULL);
	iop_unlock(&lockWorkServer);
	return isTrue;
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
			>> user._classid >> user._role;

        // user._classid = ClassidNotLogin;  // TODO

		user._role -= '0';
		map_userinfo.insert(make_pair(user._uid, user));
        map_alluser.insert(make_pair(string(reinterpret_cast<char*> (user._username)),
                                     user._uid));
	}
	fclose(fp);
}

CWSServer* CAgentServer::createClass() {
    iop_lock(&lockPortqueue);
	int port = port_queue.front();
	port_queue.pop();
    iop_unlock(&lockPortqueue);
	
	iop_lock(&lockWorkServer);
    CWSServer* pWorker = new CWSServer(port, 1);		// ����һ���µ�WorkServer
    if (!pWorker->Start(port)) {
        delete pWorker;
        pWorker = NULL;
    }
#ifdef _DEBUG_INFO_
	cout << "Worker Server Start successfully on Port " << port << "." << endl;
#endif
	iop_unlock(&lockWorkServer);

    return pWorker;
}

void CAgentServer::destroyClass(TS_UINT64 classid) {
    CWSServer* pServer = getServerByClassid(classid);
	if (NULL == pServer)
		return;

	int port = pServer->getPort();		// ��ȡ�������˿�
	delete pServer;

#ifdef _DEBUG_INFO_
	cout << "Worker Server Stop successfully on Port " << port << "." << endl;
#endif
	iop_lock(&lockWorkServer);
	delete map_workserver[classid];
	map_workserver.erase(classid);
	iop_unlock(&lockWorkServer);
		
	iop_lock(&lockPortqueue);
	port_queue.push(port);				// �������˿ڶ���
	iop_unlock(&lockPortqueue);
}

void CAgentServer::scanAgent() {
    while (isRunning()) {
        iop_usleep(HeartBeatInterval);

        TS_UINT64 currentTime = getServerTime();

        if (heartBeatTime.empty())
            continue;

        /* do not make offline now TODO
        iop_lock(&lockOfflineMaps);
        int maxAllowedInterval = HeartBeatInterval * 3;
        for (auto iter = heartBeatTime.begin(); iter != heartBeatTime.end(); ) {
#ifdef _DEBUG_INFO_
            cout << iter->first << " lost " << currentTime - iter->second << endl;
#endif
			// TODO iter->second may be a little bigger than currentTime
            if (currentTime - iter->second > maxAllowedInterval) {
                cout << iter->first << "drop connection" << currentTime - iter->second << endl;
                TS_PEER_MESSAGE msg;

                CWSServer* pServer = getServerByClassid(map_userinfo[iter->first]._classid);
                if (pServer != NULL) {
					iop_lock(&lockWorkServer);
                    pServer->removePeer(iter->first);
					iop_unlock(&lockWorkServer);
                }
                userLogoutNotify(msg, iter->first);
                offlineUsers.insert(iter->first);
                heartBeatTime.erase(iter++);
            } else {
                iter++;
            }
        }
        iop_unlock(&lockOfflineMaps);
        */

		iop_lock(&lockWorkServer);
		for (auto iter2 = map_workserver.begin(); iter2 != map_workserver.end(); ) {
			if (iter2->second == NULL) {			// ��֪��Ϊʲô���������⣬���Ǻô��ǽ���� = =  ����������ԭ���� map_workerserver[0] = NULL �±긳ֵ
				map_workserver.erase(iter2++);		// mapĪ���������һ�� ��0�� 0�� �������sendMaxSeqList()�У�Ŀ�������send������
				continue;
			}
			
            auto server = iter2->second->server;
            if (NULL == server) {
                map_workserver.erase(iter2++);
                continue;
            }

            TS_PEER_MESSAGE pmsg;
			if (server->getPort() == ClassidNotInclass) {
                sendAllClassesInfo(pmsg, iter2->first);
            } else {
                server->sendMaxSeqList();

                sendUserList(pmsg, server);
            }
            iter2++;
		}
		iop_unlock(&lockWorkServer);
    }
}

void CAgentServer::sendToQueue(TS_PEER_MESSAGE& pmsg, unsigned char type, WORD size) {
    TS_MESSAGE_HEAD* head = reinterpret_cast<TS_MESSAGE_HEAD*> (&pmsg.msg);
    head->UID = ServerUID;
    head->type = type;
    head->size = size;
    head->sequence = 0;
    head->time = getServerTime();
    head->version = VersionNumber;
    WriteOut(pmsg);
}

WORD CAgentServer::checkUsernamePassword(UserBase& user) {
    enum MsgResult result = ErrorUnknown;
    // find user in usermap by username, then check password
    auto findUser = map_alluser.find(string(reinterpret_cast<char*> (user._username)));
    if (findUser == map_alluser.end()) {
        result = ErrorUsername;
    } else if (strcmp(reinterpret_cast<char*> (map_userinfo[findUser->second]._password),
                      reinterpret_cast<char*> (user._password)) != 0) {
        result = ErrorPassword;
    } else {
        user._uid = findUser->second;
        user._role = map_userinfo[findUser->second]._role;
        result = SuccessEnterClass;
    }
    return result;
}

bool CAgentServer::enterClass(TS_PEER_MESSAGE& inputMsg, UserBase user) {
    enum MsgResult result = static_cast<enum MsgResult> (checkUsernamePassword(user));
	
	iop_lock(&lockWorkServer);
    CWSServer* pServer = getServerByClassid(user._classid);
	map_userinfo[user._uid]._classid = user._classid;				// classid �ɱ�
	iop_unlock(&lockWorkServer);
	
    DOWN_AGENTSERVICE* down = reinterpret_cast<DOWN_AGENTSERVICE*> (&inputMsg.msg);	// ����༶�ɹ����ѷ�������Ϣ���߿ͻ���
	down->result = result;
	down->uid = user._uid;
    down->role = static_cast<enum RoleOfClass> (user._role);
	
	iop_lock(&lockWorkServer);
    if (NULL == pServer) {
		/*
        down->result = ErrorNoclass;
		sendToQueue(inputMsg, ENTERCLASS, sizeof(DOWN_AGENTSERVICE));
        return false;
		*/

		WorkServerInfo* wsi = new WorkServerInfo;
		pServer = wsi->server = createClass();
		map_userinfo[user._uid]._classid = pServer->getPort();
		if (NULL != wsi->server) {
            if (NULL == pServer) {
                iop_unlock(&lockWorkServer);
                return false;	// TODO create class failed
            }
			// int port = wsi->server->getPort();
			map_workserver[wsi->server->getPort()] = wsi;
		}

	} 
	iop_unlock(&lockWorkServer);

	down->lastSeq = pServer->getMaxSeqOfUID(down->uid);
    down->addr = *pServer->getServerAddr();							// server�ĵ�ַ���뵽������
	memcpy(reinterpret_cast<char*> (down->className), pServer->className(), 40);
	sendToQueue(inputMsg, ENTERCLASS, sizeof(DOWN_AGENTSERVICE));

	auto loginUsers = pServer->getPeers();
	if (loginUsers->find(user._uid) != loginUsers->end()) {					// ��½�����Ƶ�ԭ����
		sockaddr_in backup = inputMsg.peeraddr;
		inputMsg.peeraddr = *loginUsers->at(user._uid)->getPeer();
		if (memcmp(&backup, &inputMsg.peeraddr, sizeof(sockaddr_in))) {		// ͬһ�ͻ����ظ���¼�򲻹�
			sendLeaveSuccess(inputMsg, WarnKickedOut);
			inputMsg.peeraddr = backup;
		}
	}

	
#ifdef _DEBUG_INFO_
	cout << "Add User: " << user._uid << "into class" << user._classid << endl; 
#endif
	if (SuccessEnterClass == result) {
		iop_lock(&lockWorkServer);
		pServer->addPeer(inputMsg.peeraddr, user._uid);					// ����ĵ�ַ��client agent�Ķ˿ڵ�ַ
		if (heartBeatTime.count(user._uid) == 0)
			heartBeatTime.insert(make_pair(user._uid, getServerTime()));
		else
			heartBeatTime[user._uid] = getServerTime();
		userLoginNotify(inputMsg, user._uid);
        // pServer->sendPrevMessage(user._uid);
		iop_unlock(&lockWorkServer);
		cout << user._username << " log in successfully" << endl;

        map_userinfo[user._uid]._classid = user._classid;
	}
	// pServer->sendMaxSeqList();
	return true;
}

void CAgentServer::sendLeaveSuccess(TS_PEER_MESSAGE& pmsg, MsgResult result) {
    DOWN_AGENTSERVICE* down = reinterpret_cast<DOWN_AGENTSERVICE*> (&pmsg.msg);	// �˳��༶�ɹ����ѷ�������Ϣ���߿ͻ���
    down->result = result;
    down->addr = pmsg.peeraddr;

    sendToQueue(pmsg, LEAVECLASS, sizeof(DOWN_AGENTSERVICE));
}

void CAgentServer::createClassResult(TS_PEER_MESSAGE& pmsg, CWSServer* server) {
    DOWN_CREATECLASS* down = reinterpret_cast<DOWN_CREATECLASS*> (&pmsg.msg);
    if (NULL == server) {
        down->failcode = ErrorUnknown;
    } else {
        WorkServerInfo *wsi = map_workserver[server->getPort()];
		if (NULL == wsi) {
			down->failcode = ErrorUnknown;
		} else {
			down->info.classid = wsi->server->getPort();
			down->info.teacherid = wsi->teacherid;
			memcpy(down->info.className, wsi->className, 40);
			memcpy(down->info.nickname, wsi->nickname, 20);
			down->failcode = Success;
		}
    }

    sendToQueue(pmsg, CREATECLASS, sizeof(DOWN_CREATECLASS));
}

void CAgentServer::enterAgent(TS_PEER_MESSAGE& inputMsg, UserBase user) {
    enum MsgResult result = static_cast<enum MsgResult> (checkUsernamePassword(user));

    DOWN_AGENTSERVICE* down = reinterpret_cast<DOWN_AGENTSERVICE*> (&inputMsg.msg);
    down->result = result;
    down->uid = user._uid;
    down->role = (enum RoleOfClass) user._role;

    map_userinfo[user._uid]._classid = ClassidNotInclass;

    sendToQueue(inputMsg, ENTERAGENT, sizeof(DOWN_AGENTSERVICE));  // create �� destroy��ͬһ���ظ�
}

void CAgentServer::leaveClass(TS_PEER_MESSAGE& inputMsg, UserBase user) {
	if (map_userinfo.count(user._uid) == 0) {						// if no user
		sendLeaveSuccess(inputMsg);
		return;
	}

	TS_UINT64 classid = user._classid;
    CWSServer* pServer = getServerByClassid(classid);
    if (NULL == pServer) {											// server��ɾ������û�
		sendLeaveSuccess(inputMsg);
        return;
	}
	
	iop_lock(&lockWorkServer);
	sendLeaveSuccess(inputMsg);
	userLogoutNotify(inputMsg, user._uid);
    pServer->removePeer(user._uid);
	heartBeatTime.erase(user._uid);
	iop_unlock(&lockWorkServer);

#ifdef _DEBUG_INFO_
	cout << "user: " << user._uid << " removed" << endl;
#endif

	if (pServer->isEmpty()) {										// ������û���˾�����
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
	
	iop_lock(&lockWorkServer);
	map<TS_UINT64, CPeerConnection*>* loginUser = pServer->getPeers();
	for (auto iter = loginUser->begin(); iter != loginUser->end(); iter++) {
		if (iter->first != uid && iter->first != ServerUID) {		// �������յ������û���Ϣ
            SERVER_CLASS_ADD_USER *down = reinterpret_cast<SERVER_CLASS_ADD_USER*> (&pmsg.msg);
			UserBase us = map_userinfo[uid];
			down->enterUser.uid = uid;
			down->enterUser.reserved = us._reserved;
			down->enterUser.classid = us._classid;
			down->enterUser.role = us._role;
			memcpy(down->enterUser.username, us._username, 20);
            pmsg.peeraddr = *iter->second->getPeer();

            sendToQueue(pmsg, ADDUSER, sizeof(SERVER_CLASS_ADD_USER));;
        }
	}
    sendUserList(pmsg, pServer);
	iop_unlock(&lockWorkServer);
}

void CAgentServer::sendUserList(TS_PEER_MESSAGE& pmsg, CWSServer* pServer) {
    if (NULL == pServer) {
        return;
    }

    map<TS_UINT64, CPeerConnection*>* loginUser = pServer->getPeers();
    SERVER_CLASS_USER_LIST *down = reinterpret_cast<SERVER_CLASS_USER_LIST*> (&pmsg.msg);

    int calc = 0;
    for (auto iter2 = map_alluser.begin(); iter2 != map_alluser.end(); iter2++) {
        if (calc == 10) {
            for (auto sendList = loginUser->begin(); sendList != loginUser->end(); sendList++) {
                pmsg.peeraddr = *sendList->second->getPeer();
                WriteOut(pmsg);
            }
            calc = 0;		// ֮ǰ��calc = 0 ��������һ��for���棬���������serverÿ�����һ���û��˳�ʱ
							// calc û����0�� Ȼ����� down->users[calc] �ڴ�Խ�� crash!!!
        }

        USER_INFO ui;
        UserBase us = map_userinfo[iter2->second];
        ui.uid = us._uid;
        ui.classid = us._classid;
        ui.reserved = us._reserved;
        ui.role = us._role;
        if (ui.role == RoleTeacher) {
            ui.isWriteable = 1;
        } else {
            ui.isWriteable = 0;
        }
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

    CWSServer* pServer = getServerByClassid(map_userinfo[uid]._classid);
	if (pServer == NULL) {
		return;
	}
	
	map<TS_UINT64, CPeerConnection*>* allUsers = pServer->getPeers();
	for (auto iter = allUsers->begin(); iter != allUsers->end(); iter++) {
		if (iter->first != uid && iter->first != ServerUID) {
            SERVER_CLASS_REMOVE_USER *down = reinterpret_cast<SERVER_CLASS_REMOVE_USER*> (&pmsg.msg);
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
    case ENTERAGENT:
  //      {
  //          UP_AGENTSERVICE* in = (UP_AGENTSERVICE*) &inputMsg.msg;		// �յ�����/�˳�Agent������
  //          UserBase user;
  //          user._classid = in->classid;
  //          user._reserved = in->head.reserved;
  //          user._uid = in->head.UID;

  //          memcpy(user._username, in->username, 20);
  //          memcpy(user._password, in->password, 20);

  //          enterAgent(inputMsg, user);									// �������Agent���󣬲��ظ�
  //      }
		//break;
	case ENTERCLASS:
		{
            UP_AGENTSERVICE* in = reinterpret_cast<UP_AGENTSERVICE*> (&inputMsg.msg);		// �յ�����/�˳��༶������
			UserBase user;
			user._classid = in->classid;
            user._reserved = in->head.reserved;
			user._uid = in->head.UID;

			memcpy(user._username, in->username, 20);
			memcpy(user._password, in->password, 20);
			
            enterClass(inputMsg, user);									// �������༶���󣬲��ظ�
		}
        break;
	case CREATECLASS:
        {
            UP_CREATECLASS* in = reinterpret_cast<UP_CREATECLASS*> (&inputMsg.msg);
            WorkServerInfo* wsi = new WorkServerInfo;
            wsi->server = createClass();
            if (NULL != wsi->server) {
                wsi->teacherid = in->uid;
                wsi->allowedStudentNum = in->allowedStudentNum;

                memcpy(wsi->className, in->className, 40);
                memcpy(wsi->nickname, in->nickname, 20);
                map_workserver[wsi->server->getPort()] = wsi;
            }

            createClassResult(inputMsg, wsi->server);
		}
		break;
	case DESTROYCLASS:
		{
            UP_DESTROYCLASS* in = reinterpret_cast<UP_DESTROYCLASS*> (&inputMsg.msg);
            WorkServerInfo* wsi = map_workserver[in->classid];
            if (NULL != wsi) {
                if (wsi->server)
                    delete wsi->server;
                map_workserver.erase(in->classid);
            }

            DOWN_CREATECLASS* down = reinterpret_cast<DOWN_CREATECLASS*> (&inputMsg.msg);
            down->failcode = Success;
            sendToQueue(inputMsg, DESTROYCLASS, sizeof(DOWN_CREATECLASS));  // create �� destroy��ͬһ���ظ�
		}
		break;
	case LEAVECLASS:
		{
            UP_AGENTSERVICE* in = reinterpret_cast<UP_AGENTSERVICE*> (&inputMsg.msg);		// �յ�����/�˳��༶������
			UserBase user;

			user._uid = in->head.UID;
			if (map_userinfo.count(user._uid) == 0)
				break;

			user._classid = map_userinfo[user._uid]._classid;
            user._reserved = in->head.reserved;

			memcpy(user._username, in->username, 20);
			memcpy(user._password, in->password, 20);

            leaveClass(inputMsg, user);							// �����˳��༶���󣬲��ظ�
		}
        break;
	case HEARTBEAT:
		{
            UP_HEARTBEAT* in = reinterpret_cast<UP_HEARTBEAT*> (&inputMsg.msg);
			TS_UINT64 uid = in->head.UID;

			if (map_userinfo.find(uid) == map_userinfo.end())
				break;
			
			if (heartBeatTime.count(uid) != 0) {				// ������ʱ�����set��
				iop_lock(&lockOfflineMaps);
				//CWSServer* pServer = getServerByUID(uid);
				//if (pServer == NULL) {
				//	createClass(map_userinfo.find(uid)->second._classid);
				//	pServer = getServerByUID(uid);
				//}
				//pServer->addPeer(inputMsg.peeraddr, in->head.UID);					// ����ĵ�ַ��client agent�Ķ˿ڵ�ַ
				//heartBeatTime.insert(make_pair(uid, in->head.time));

				heartBeatTime[uid] = in->head.time;

				if (offlineUsers.count(uid) > 0)					// ���������Ѿ������û�
					offlineUsers.erase(uid);						// ����ȡ������״̬
				iop_unlock(&lockOfflineMaps);
            }
		}
        break;
	case SCANPORT:
		{
            TS_MESSAGE_HEAD* head = reinterpret_cast<TS_MESSAGE_HEAD*> (&inputMsg.msg);
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
	CWSServer* result;

	iop_lock(&lockWorkServer);
    if (map_userinfo.count(uid) == 0) {
        result = NULL;
    }
    result = getServerByClassid(map_userinfo[uid]._classid);
	iop_unlock(&lockWorkServer);

	return result;
}

CWSServer* CAgentServer::getServerByClassid(TS_UINT64 classid) {
    CWSServer* result;
    iop_lock(&lockWorkServer);
	auto iter = map_workserver.find(classid);
	if (map_workserver.end() == iter) {
		result = NULL;
	} else {
		result = map_workserver[classid]->server;
	}
    iop_unlock(&lockWorkServer);
    return result;
}

void CAgentServer::sendAllClassesInfo(TS_PEER_MESSAGE& pmsg, TS_UINT64 uid) {
    pmsg = pmsg;
    uid = uid;
}
