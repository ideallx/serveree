#include <QTime>
#include <QFile>
#include "CClientNet.h"


thread_ret_type thread_func_call HBProc(LPVOID lpParam) {
    CClientNet* c = (CClientNet*) lpParam;
    if (!c) {
        iop_thread_exit(0);
        return 0;
    }
    c->sendHeartBeat();
#ifdef _DEBUG_INFO_
    cout << "hb thread exit" << endl;
#endif
    iop_thread_exit(0);
    return 0;
}


CClientNet::CClientNet()
    : m_seq(1)
	, m_agent(NULL)
	, m_timeDiff(0) {
    QTime time = QTime::currentTime();
    qsrand(time.msec() + time.second() * 1000);
    m_Connect = dynamic_cast<CReliableConnection*> (pConnect);
    setUID(qrand());
}

CClientNet::~CClientNet() {
    iop_thread_cancel(pthread_hb);
	DESTROY(m_agent);
}

bool CClientNet::Start(unsigned short port) {
    if (!CServer::Start(port))
        return false;

    DESTROY(m_agent);
    m_Connect->addPeer(ServerUID, m_Addr);
    m_agent = new CPeerConnection(m_Connect->getSocket());
    if (!m_agent->isValidSocket())
        return false;

    m_agent->setPeer(m_Addr);
	return isRunning();
}

DWORD CClientNet::MsgHandler(TS_PEER_MESSAGE& inputMsg) {			// 创建新的客户端WSClient
    TS_UINT64 uid = getUid(inputMsg.msg);
    if (uid == SelfUID) {
        return 0;
    }

    TS_MESSAGE_HEAD *head = (TS_MESSAGE_HEAD*) &inputMsg.msg;
    QFile f("aa.txt");
    f.open(QIODevice::Append);
    QString str = QString::number(getType(inputMsg.msg)).toLocal8Bit().data();
    str += " " + QString::number(head->sequence) + " ";
    str += QString::number(head->subSeq) + " ";
    str += QString::number(head->UID);
    f.write(str.toLocal8Bit().data());
    f.write("\r\n");
    f.close();

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
    Q_UNUSED(wParam);
    Q_UNUSED(lParam);
    if (!isremote)
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
    qDebug() << head->sequence << head->subSeq;
	
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
    Q_UNUSED(s_code);
	m_Addr = addr;
}

void CClientNet::setUID(TS_UINT64 uid) {
    m_uid = uid;
    globalUID = uid;
    m_Connect->setUID(m_uid);
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
        if (pConnect->recv(pmsg->msg.Body, msglen) > 0) {
            WriteIn(*pmsg);
		} else {
			iop_usleep(100);
		}
	}
	delete pmsg;
#ifdef _DEBUG_INFO_
	cout << "recv thread exit" << endl;
#endif
}

void CClientNet::sendProc() {
	TS_PEER_MESSAGE *pmsg = new TS_PEER_MESSAGE();
	memset(pmsg, 0, sizeof(TS_PEER_MESSAGE));

    iop_usleep(10);
	int result;
	
	while (isRunning()) {
        ReadOut(*pmsg);
		if (getType(pmsg->msg) > PACKETCONTROL)
			result = m_agent->send(pmsg->msg.Body, packetSize(pmsg->msg));
		else
            result = m_Connect->send(pmsg->msg.Body, packetSize(pmsg->msg));
	}
	delete pmsg;
#ifdef _DEBUG_INFO_
	cout << "send thread exit" << endl;
#endif
}

void CClientNet::startupHeartBeat() {
    int rc = iop_thread_create(&pthread_hb, HBProc, (void *) this, 0);
	if (0 == rc) {
		iop_usleep(10);
#ifdef _DEBUG_INFO_
		cout << "Heart Beat Thread start successfully " << endl;
#endif
	} else {
		turnOff();
	}
}

void CClientNet::endHeartBeat() {
    iop_thread_cancel(pthread_hb);
}

// throooooough the NAT, type must < PACKETCONTROL
void CClientNet::sendConnectionMsg() {
    ts_msg msg;
	TS_MESSAGE_HEAD *head = (TS_MESSAGE_HEAD*) &msg;

	head->type = CONNECTION;
    head->time = getClientTime(m_timeDiff);
    head->size = sizeof(TS_MESSAGE_HEAD);
    head->sequence = 0;
    head->UID = m_uid;
    head->version = VersionNumber;
    head->subSeq = 0;

	for (int i = 0; i < 5; i++) 
		m_Connect->send(msg.Body, packetSize(msg));
}

void CClientNet::sendHeartBeat() {
   ts_msg msg;
    while (isRunning()) {
        UP_HEARTBEAT* upcmd = (UP_HEARTBEAT*) &msg;

        upcmd->head.type = HEARTBEAT;
        upcmd->head.time = getClientTime(m_timeDiff);
        upcmd->head.size = sizeof(UP_HEARTBEAT);
        upcmd->head.sequence = 0;
        upcmd->head.UID = m_uid;
        upcmd->head.version = VersionNumber;
        upcmd->head.subSeq = 0;
        upcmd->maxSeq = m_seq - 1;

		m_agent->send(msg.Body, upcmd->head.size);
#ifdef _DEBUG_INFO_
        cout << m_uid << "send heart beat at " << upcmd->head.time << endl;
#endif
        iop_usleep(HeartBeatInterval);				// 1分钟一个
    }
}

void CClientNet::addServerAddr(sockaddr_in in) { 
	m_Connect->addPeer(ServerUID, in); 
}

