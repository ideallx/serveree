#include "CServer.h"
#include "../Connections/CReliableConnection.h"

CServer::CServer() :
	MsgLen(MESSAGE_SIZE),

#ifdef _MULTI_THREAD_SERVER_
    recvthread_num(1),
    sendthread_num(1),
    msgthread_num(1),
#else
    recvthread_num(1),
    sendthread_num(1),
    msgthread_num(1),
#endif


	p_InMsgQueue(new TSQueue<TS_PEER_MESSAGE>),
	p_OutMsgQueue(new TSQueue<TS_PEER_MESSAGE>) {
		
    pthread_recv = new iop_thread_t[recvthread_num],
    pthread_send = new iop_thread_t[sendthread_num],
    pthread_msg = new iop_thread_t[msgthread_num],

	Port = 0;
	pConnect = new CReliableConnection;

    data_in = CreateSemaphore(NULL, 0, 102400, NULL);
    data_out = CreateSemaphore(NULL, 0, 102400, NULL);
}

CServer::~CServer(void) {
    Stop();
    delete pConnect;

	CloseHandle(data_in);
	CloseHandle(data_out);

	DESTROY(p_InMsgQueue);
	DESTROY(p_OutMsgQueue);
}

TS_UINT64 CServer::AllocateSessionID(void) {
	return getServerTime();
}

bool CServer::Initialize(void) {
	return TRUE;
}

bool CServer::Uninitialize(void) {
	pConnect->clear();
	return TRUE;
}


void CServer::ReadIn(TS_PEER_MESSAGE& pmsg) {
    WaitForSingleObject(data_in, INFINITE);
	p_InMsgQueue->deQueue(pmsg);
}

void CServer::WriteIn(const TS_PEER_MESSAGE& pmsg) {
    p_InMsgQueue->enQueue(pmsg);
	ReleaseSemaphore(data_in, 1, NULL);
}

void CServer::ReadOut(TS_PEER_MESSAGE& pmsg) {
    WaitForSingleObject(data_out, INFINITE);
	p_OutMsgQueue->deQueue(pmsg);
}

void CServer::WriteOut(const TS_PEER_MESSAGE& pmsg) {
    p_OutMsgQueue->enQueue(pmsg);
	ReleaseSemaphore(data_out, 1, NULL);
}


bool CServer::ReadIniFile(void) {
	return TRUE;
}

bool CServer::Start(unsigned short port) {
	// CConnection or Queue
	if (pConnect == NULL 
		|| p_InMsgQueue == NULL 
		|| p_OutMsgQueue == NULL 
		|| isStarted)
		return FALSE;

	Port = port;

	if (!pConnect->create(port)) {
		return FALSE;
	}

	turnOn();
	if (!Initialize ())
		return FALSE;

	for (unsigned int i = 0; i < recvthread_num; i++) {
        int rc = iop_thread_create(&pthread_recv[i], RecvProc, (void *) this, 0);
		if (0 == rc) {
			iop_usleep(10);
#ifdef _DEBUG_INFO_
			cout << "Recv Thread start successfully " << endl;
#endif
		} else {
			turnOff();
		}
	}


	for (unsigned int i = 0; i < sendthread_num; i++) {
        int rc = iop_thread_create(&pthread_send[i], SendProc, (void *) this, 0);
		if (0 == rc) {
			iop_usleep(10);
#ifdef _DEBUG_INFO_
			cout << "Send Thread start successfully " << endl;
#endif
		} else {
			turnOff();
		}
	}

	for (unsigned int i = 0; i < msgthread_num; i++) {
        int rc = iop_thread_create(&pthread_msg[i], MsgProc, (void *) this, 0);
		if( rc == 0 ){
			iop_usleep(10);
#ifdef _DEBUG_INFO_
			cout << "Msg Thread start successfully" << endl;
#endif
		} else {
			turnOff();
		}
	}
	return isRunning();
}

bool CServer::Stop(void) {
    Uninitialize();
    if (isRunning()) {
        turnOff();
        iop_usleep(100);
        for (unsigned int i = 0; i < sendthread_num; i++) {
            iop_thread_cancel(pthread_send[i]);
		}
        for (unsigned int i = 0; i < recvthread_num; i++) {
            iop_thread_cancel(pthread_recv[i]);
		}
        for (unsigned int i = 0; i < msgthread_num; i++) {
            iop_thread_cancel(pthread_msg[i]);
		}
		delete[] pthread_send;
		delete[] pthread_recv;
		delete[] pthread_msg;
    }
	return TRUE;
}

DWORD CServer::MsgHandler(TS_PEER_MESSAGE& pmsg) {
	return 0;
}

void CServer::sendProc() {
	TS_PEER_MESSAGE pmsg;
	memset(&pmsg, 0, sizeof(TS_PEER_MESSAGE));

	CAbsConnection* pPeerConn = new CPeerConnection();
	if (!pPeerConn->copy(getConnection())) {
		return;
	}
	while (isRunning()) {
		ReadOut(pmsg);
		pPeerConn->setPeer(pmsg.peeraddr);
        pPeerConn->send(pmsg.msg.Body, sizeof(ts_msg));

#ifdef _DEBUG_INFO_
		cout << "port:" << pPeerConn->getPeer()->sin_port << endl;
#endif
	}
}

void CServer::msgProc() {
	TS_PEER_MESSAGE pmsg;
	memset(&pmsg, 0, sizeof(TS_PEER_MESSAGE));

	while (isRunning()) {
		memset(&pmsg, 0, sizeof(TS_PEER_MESSAGE));
		ReadIn(pmsg);
		MsgHandler(pmsg);
	}
	cout << "msg thread exit" << endl;
}

void CServer::recvProc() {
	ULONG msglen = sizeof(ts_msg);
	TS_PEER_MESSAGE pmsg;
	memset(&pmsg, 0, sizeof(TS_PEER_MESSAGE));

	CAbsConnection* pConn = new CPeerConnection();
	if (!pConn->copy(getConnection())) {
		return;
	}

	while (isRunning()) {
		memset(&pmsg, 0, sizeof(TS_PEER_MESSAGE));
		if (pConn->recv(pmsg.msg.Body, msglen) > 0) {
			memcpy(&pmsg.peeraddr, pConn->getRecvAddr(), sizeof(struct sockaddr_in));
			WriteIn(pmsg);
		}
	}
#ifdef _DEBUG_INFO_
	cout << "recv thread exit" << endl;
#endif
}
