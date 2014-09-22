#include "CClientNet.h"

CClientNet::CClientNet() :
	m_seq(1),
	m_uid(0),
	m_agent(NULL),
	m_timeDiff(0) {
	m_Connect = dynamic_cast<CReliableConnection*> (pConnect);
}

CClientNet::~CClientNet() {
	Stop();										// ���û��ֹͣ����ֹͣ���ݷ���
	Sleep(100);									// �ȴ����߳��˳�
	
	delete m_agent;
	m_Connect->stop();							// ��Դ��ַ�����ɾ��
}

bool CClientNet::Start(unsigned short port) {
	if (0 == m_uid) {							// û�����ñ����û�
		return FALSE;
	}

	CServer::Start(port);

	m_agent = new CPeerConnection(m_Connect->getSocket());
	m_agent->copy(m_Connect);
	assert(m_agent->getSocket()->getSocket() > 0);
	m_agent->setPeer(m_Addr);
	
	turnOn();
	if (!Initialize ())
		return FALSE;

	return isRunning();
};

DWORD CClientNet::MsgHandler(TS_PEER_MESSAGE& inputMsg) {			// �����µĿͻ���WSClient													// �����ϲ�
	sendToUpper(inputMsg.msg, 0, 0, true);
	return 0;
}

void CClientNet::msgProc() {
	TS_PEER_MESSAGE *pmsg = new TS_PEER_MESSAGE();
	memset(pmsg, 0, sizeof(TS_PEER_MESSAGE));

	while (isRunning()) {
		memset(pmsg, 0, sizeof(TS_PEER_MESSAGE));
		ReadIn(*pmsg);
		MsgHandler(*pmsg);
	}
	delete pmsg;
}

void CClientNet::ProcessMessage(ts_msg& msg, WPARAM wParam, LPARAM lParam, BOOL isremote) {
	//TS_MESSAGE_HEAD* head = (TS_MESSAGE_HEAD*) &msg;

	//  if (isremote) {
	//	switch (head->type) {
	//	case AddAddr:
	//		m_Connect->
	//		break;
	//	case RemoveAddr:

	//		break;
	//	}

	buildSendMessage(msg);
}

void CClientNet::buildSendMessage(ts_msg& msg) {
	TS_MESSAGE_HEAD* head = (TS_MESSAGE_HEAD*) &msg;
	head->time = getClientTime(m_timeDiff);
	head->sequence = m_seq++;
	head->isEnd = 0;
	head->UID = m_uid;
	head->version = VersionNumber;
	
	TS_PEER_MESSAGE pmsg;
	pmsg.msg = msg;
	WriteOut(pmsg);
}

void CClientNet::SetServerAddr(DWORD s_code, char* ip, WORD port){		// �趨��Ϣ��Ҫ���ͳ�ȥ���ⲿ��������ַ
	struct sockaddr_in addr;
	MakeIPv4Addr(addr, ip, port);
	SetServerAddr(s_code, addr);
};

void CClientNet::SetServerAddr(DWORD s_code, struct sockaddr_in addr){	// �趨��Ϣ��Ҫ���ͳ�ȥ���ⲿ��������ַ
	m_Connect->addPeer(ServerUID, addr);
	m_Addr = addr;
};

void CClientNet::MakeIPv4Addr(struct sockaddr_in& addr, char* ip, WORD port) {
	addr.sin_addr.s_addr = inet_addr(ip);
	addr.sin_port = htons(port);
	addr.sin_family = AF_INET;
};

void CClientNet::recvProc() {	
	ts_msg msg;
	ULONG msglen = sizeof(ts_msg);
	TS_PEER_MESSAGE *pmsg = new TS_PEER_MESSAGE();
	memset(pmsg, 0, sizeof(TS_PEER_MESSAGE));
	
	while (isRunning()) {
		if (m_Connect->recv(pmsg->msg.Body, msglen) > 0) {
			WriteIn(*pmsg);
		} else {
			Sleep(1);
		}
	}
	delete pmsg;
	cout << "recv thread exit" << endl;
}

void CClientNet::sendProc() {
	TS_PEER_MESSAGE *pmsg = new TS_PEER_MESSAGE();
	memset(pmsg, 0, sizeof(TS_PEER_MESSAGE));

	Sleep(1000);
	
	while (isRunning()) {
		ReadOut(*pmsg);										// ��ͨ����pConnect����
		// cout << "0";
		int result = m_Connect->send(pmsg->msg.Body, packetSize(pmsg->msg));
	}
	delete pmsg;
	cout << "send thread exit" << endl;
}

void CClientNet::startupHeartBeat() {
	pthread_t pthread_hb;	// heartbeat
	int rc = pthread_create(&pthread_hb, NULL, HBProc, (void*) this);
	if (0 == rc) {
		iop_usleep(10);
		cout << "Heart Beat Thread start successfully " << endl;
	} else {
		turnOff();
	}
}

void CClientNet::sendHeartBeat() {
	TS_PEER_MESSAGE *msg = new TS_PEER_MESSAGE();
	UP_HEARTBEAT* upcmd = (UP_HEARTBEAT*) &msg->msg;
	
	upcmd->head.type = HEARTBEAT;
	upcmd->head.time = getClientTime(m_timeDiff);
	upcmd->head.size = sizeof(UP_HEARTBEAT);
	upcmd->head.sequence = 0;
	upcmd->head.UID = m_uid;
	upcmd->head.version = VersionNumber;
	
	m_agent->send(msg->msg.Body, packetSize(msg->msg));
	cout << m_uid << "send heart beat at " << upcmd->head.time << endl;
	delete msg;
}

void* HBProc(LPVOID lpParam) {
	CClientNet* c = (CClientNet*) lpParam;
	if (!c) {
		return 0;
	}
	while (c->isRunning()) {
		c->sendHeartBeat();
		Sleep(HeartBeatInterval);				// 1����һ��
	}
	return 0;
}

