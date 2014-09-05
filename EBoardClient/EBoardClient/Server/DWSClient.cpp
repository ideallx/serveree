#include "DWSClient.h"

extern string int2string(TS_UINT64);

DWSClient::DWSClient() :
	_seq(0),
	ub(NULL),
	agent(NULL),
	timeDiff(0) {
	conn = dynamic_cast<CReliableConnection*> (pConnect);
}

DWSClient::~DWSClient() {
	delete ub;
	delete agent;
}

void DWSClient::recvProc() {
	ULONG msglen = sizeof(ts_msg);
	TS_PEER_MESSAGE *pmsg = new TS_PEER_MESSAGE();
	memset(pmsg, 0, sizeof(TS_PEER_MESSAGE));
	
	while (isRunning()) {
		if (conn->recv(pmsg->msg.Body, msglen) > 0)
			WriteIn(*pmsg);
	}
	delete pmsg;
	cout << "recv thread exit" << endl;
}

void DWSClient::msgProc() {
	TS_PEER_MESSAGE *pmsg = new TS_PEER_MESSAGE();
	memset(pmsg, 0, sizeof(TS_PEER_MESSAGE));

	while (isRunning()) {
		memset(pmsg, 0, sizeof(TS_PEER_MESSAGE));
		ReadIn(*pmsg);
		MsgHandler(*pmsg);
	}
	delete pmsg;
}

void DWSClient::setUser(UserBase& ubin) {			// 设置本机信息
	if (NULL == ub) {
		ub = new UserBase();
	}
	memcpy(ub, &ubin, sizeof(UserBase));
	conn->setUID(ub->_uid);
}

void DWSClient::sendProc() {
	TS_PEER_MESSAGE *pmsg = new TS_PEER_MESSAGE();
	memset(pmsg, 0, sizeof(TS_PEER_MESSAGE));

	enterClass(pmsg->msg);
	if (agent->send(pmsg->msg.Body, sizeof(ts_msg)) < 0)	// 控制类由Agent发送
		cout << "send error in sendproc" << endl;
	
	while (isRunning()) {
		ReadOut(*pmsg);										// 普通类由pConnect发送
		// cout << ub->_uid << ":" << "send " << getSeq(pmsg->msg) << endl;
		int result = conn->send(pmsg->msg.Body, packetSize(pmsg->msg));
	}
	delete pmsg;
	cout << "send thread exit" << endl;
}

// 生成测试数据
bool DWSClient::generateData() {
	TS_PEER_MESSAGE *msg = new TS_PEER_MESSAGE();

	if (_seq > 2000000)
		return false;

	int length = rand() % 500 + 525;
	TS_MESSAGE_HEAD* head = (TS_MESSAGE_HEAD*) &msg->msg;

	head->time = getClientTime(timeDiff);
	head->size = length;
	head->sequence = ++_seq;
	head->isEnd = 0;
	head->UID = ub->_uid;
	head->version = 100;
	
	WriteOut(*msg);
	iop_usleep(10);			// 时间间隔
	delete msg;
	return true;
}

void DWSClient::sendHeartBeat() {
	TS_PEER_MESSAGE *msg = new TS_PEER_MESSAGE();
	UP_HEARTBEAT* upcmd = (UP_HEARTBEAT*) &msg->msg;
	
	upcmd->head.type = HEARTBEAT;
	upcmd->head.time = getClientTime(timeDiff);
	upcmd->head.size = sizeof(UP_HEARTBEAT);
	upcmd->head.sequence = 0;
	upcmd->head.UID = ub->_uid;
	upcmd->head.version = 100;
	
	agent->send(msg->msg.Body, packetSize(msg->msg));
	cout << ub->_uid << "send heart beat at " << upcmd->head.time << endl;
	delete msg;
}

bool DWSClient::Start(unsigned short port) {
	// CConnection or Queue
	if (pConnect == NULL 
		|| p_InMsgQueue == NULL 
		|| p_OutMsgQueue == NULL 
		|| isStarted)
		return FALSE;

	Port = port;

	if (!pConnect->create(0)) {
		return FALSE;
	}
	
	SOCKADDR_IN addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr("192.168.1.202");
	addr.sin_port = htons(port);
	agent = new CPeerConnection(conn->getSocket());
	agent->copy(conn);
	assert(agent->getSocket()->getSocket() > 0);
	agent->setPeer(addr);

	turnOn();
	if (!Initialize ())
		return false;

	for (unsigned int i = 0; i < recvthread_num; i++) {
		int rc = pthread_create(&pthread_recv[i], NULL, RecvProc, (void*) this);
		if (0 == rc) {
			iop_usleep(10);
			cout << "Recv Thread start successfully " << endl;
		} else {
			turnOff();
		}
	}


	for (unsigned int i = 0; i < sendthread_num; i++) {
		int rc = pthread_create(&pthread_send[i], NULL, SendProc, (void*) this);
		if (0 == rc) {
			iop_usleep(10);
			cout << "Send Thread start successfully " << endl;
		} else {
			turnOff();
		}
	}

	for (unsigned int i = 0; i < msgthread_num; i++) {
		int rc = pthread_create(&pthread_msg[i], NULL, MsgProc, (void*) this);
		if (rc == 0) {
			iop_usleep(10);
			cout << "Msg Thread start successfully" << endl;
		} else {
			turnOff();
		}
	}

	return isRunning();
}

void* GenProc(LPVOID lpParam) {
	pthread_detach(pthread_self());
	DWSClient* c = (DWSClient*) lpParam;
	if (!c) {
		return 0;
	}
	while (c->generateData());		// 生成包
	return 0;
}

void* HBProc(LPVOID lpParam) {
	pthread_detach(pthread_self());
	DWSClient* c = (DWSClient*) lpParam;
	if (!c) {
		return 0;
	}
	while (c->isRunning()) {
		c->sendHeartBeat();
		Sleep(HeartBeatInterval);				// 1分钟一个
	}
	return 0;
}

DWORD DWSClient::MsgHandler(TS_PEER_MESSAGE& inputMsg) {			// 创建新的客户端WSClient
	enum PacketType type = getType(inputMsg.msg);
	DOWN_AGENTSERVICE* in = (DOWN_AGENTSERVICE*) &inputMsg.msg;
	if (ENTERCLASS == in->head.type) {
		if (in->result == Success) {								// 进入班级成功，创建work client
			conn->addPeer(ServerUID, in->addr);

			timeDiff = in->head.time - GetTickCount();

			pthread_t pthread_gen;
			int rc = pthread_create(&pthread_gen, NULL, GenProc, (void*) this);
			if (0 == rc) {
				iop_usleep(10);
				cout << "Data Generate Thread start successfully " << endl;
			} else {
				turnOff();
			}

			pthread_t pthread_hb;	// heartbeat
			rc = pthread_create(&pthread_hb, NULL, HBProc, (void*) this);
			if (0 == rc) {
				iop_usleep(10);
				cout << "Data Generate Thread start successfully " << endl;
			} else {
				turnOff();
			}
			conn->setFilePrefix(int2string(ub->_classid) + "_" + int2string(in->head.time));
		}
	} else if (LEAVECLASS == in->head.type) {
		Stop();
	}
	return 0;
}

bool DWSClient::enterClass(ts_msg& msg) {			// 拼接进入班级的报文
	if (NULL == ub)
		return false;

	TS_UINT64 uid = ub->_uid;
	UP_AGENTSERVICE* upcmd = (UP_AGENTSERVICE*) &msg;
	upcmd->head.time = getClientTime(timeDiff);
	upcmd->head.type = ENTERCLASS;
	upcmd->head.UID = uid;
	upcmd->head.reserved = ub->_reserved;
	upcmd->classid = ub->_classid;
	upcmd->role = static_cast<enum RoleOfClass> (ub->_role);
	memcpy(upcmd->username, ub->_username, 20);
	memcpy(upcmd->password, ub->_password, 20);
	return true;
}

bool DWSClient::leaveClass(ts_msg& msg) {
	if (NULL == ub)
		return false;

	TS_UINT64 uid = ub->_uid;
	UP_AGENTSERVICE* upcmd = (UP_AGENTSERVICE*) &msg;

	upcmd->head.time = getClientTime(timeDiff);
	upcmd->head.type = LEAVECLASS;
	upcmd->head.UID = uid;
	upcmd->head.reserved = ub->_reserved;
	upcmd->classid = ub->_classid;
	upcmd->role = static_cast<enum RoleOfClass> (ub->_role);
	memcpy(upcmd->username, ub->_username, 20);
	memcpy(upcmd->password, ub->_password, 20);
	return true;
}
