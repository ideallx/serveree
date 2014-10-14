#include <QTime>
#include "CClientNet.h"

CClientNet::CClientNet() :
    m_seq(1),
	m_agent(NULL),
	m_timeDiff(0) {

    QTime time = QTime::currentTime();
    qsrand(time.msec()+time.second()*1000);
    m_uid = qrand();
    globalUID = m_uid;

	m_Connect = dynamic_cast<CReliableConnection*> (pConnect);
    m_Connect->setUID(m_uid);
}

CClientNet::~CClientNet() {
    Stop();										// 如果没有停止则先停止数据服务
    delete m_agent;
}

bool CClientNet::Start(unsigned short port) {
    CServer::Start(port);

	m_agent = new CPeerConnection(m_Connect->getSocket());
	m_agent->copy(m_Connect);
	assert(m_agent->getSocket()->getSocket() > 0);
	m_agent->setPeer(m_Addr);

	turnOn();
	if (!Initialize ())
		return FALSE;

	return isRunning();
}

DWORD CClientNet::MsgHandler(TS_PEER_MESSAGE& inputMsg) {			// 创建新的客户端WSClient
    TS_UINT64 uid = getUid(inputMsg.msg);
    TS_MESSAGE_HEAD* head = (TS_MESSAGE_HEAD*) &inputMsg.msg;
    if ((uid == m_uid) || uid == SelfUID) {
        return 0;
    }
    sendToAll(inputMsg.msg, 0, 0, true);
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
    if (getType(msg) > PACKETCONTROL) {
        head->sequence = 0;
    } else {
        head->sequence = m_seq++;
    }
    head->isEnd = 0;
    head->UID = m_uid;
    head->version = VersionNumber;
	
    TS_PEER_MESSAGE pmsg;
    pmsg.msg = msg;
    WriteOut(pmsg);
}

void CClientNet::SetServerAddr(DWORD s_code, char* ip, WORD port){		// 设定消息将要发送出去的外部服务器地址
	struct sockaddr_in addr;
	MakeIPv4Addr(addr, ip, port);
	SetServerAddr(s_code, addr);
}

void CClientNet::SetServerAddr(DWORD s_code, struct sockaddr_in addr){	// 设定消息将要发送出去的外部服务器地址
	m_Connect->addPeer(ServerUID, addr);
	m_Addr = addr;
}

void CClientNet::MakeIPv4Addr(struct sockaddr_in& addr, char* ip, WORD port) {
	addr.sin_addr.s_addr = inet_addr(ip);
	addr.sin_port = htons(port);
	addr.sin_family = AF_INET;
}

void CClientNet::recvProc() {
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

    Sleep(10);
	int result;
	
	while (isRunning()) {
        ReadOut(*pmsg);
		if (getType(pmsg->msg) > PACKETCONTROL)
			result = m_agent->send(pmsg->msg.Body, packetSize(pmsg->msg));
		else
            result = m_Connect->send(pmsg->msg.Body, packetSize(pmsg->msg));
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

void CClientNet::addServerAddr(sockaddr_in in) { 
	m_Connect->addPeer(ServerUID, in); 
}


void* HBProc(LPVOID lpParam) {
	CClientNet* c = (CClientNet*) lpParam;
	if (!c) {
		return 0;
	}
	while (c->isRunning()) {
		c->sendHeartBeat();
		Sleep(HeartBeatInterval);				// 1分钟一个
	}
    cout << "hb thread exit" << endl;
	return 0;
}

