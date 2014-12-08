#include "CServer.h"
#include "../Connections/CReliableConnection.h"

CServer::CServer()
	: MsgLen(MESSAGE_SIZE)
#ifdef _MULTI_THREAD_SERVER_
    , recvthread_num(5)
    , sendthread_num(2)
    , msgthread_num(3)
#else
    , recvthread_num(1)
    , sendthread_num(1)
    , msgthread_num(1)
#endif
	, pthread_recv(new iop_thread_t[recvthread_num])
	, pthread_send(new iop_thread_t[sendthread_num])
	, pthread_msg(new iop_thread_t[msgthread_num]){
	Port = 0;
	pConnect = new CReliableConnection;
}

CServer::~CServer(void) {
    Stop();
	DESTROY(pConnect);
}

bool CServer::Start(unsigned short port) {
	// CConnection or Queue
	if (pConnect == NULL 
		|| p_InMsgQueue == NULL 
		|| p_OutMsgQueue == NULL 
		|| isStarted)
		return false;

	Port = port;
	isStarted = true;	// u must start before create thread or thread will exit soon

	if (!pConnect->create(port)) {
		return false;
	}
	
	for (unsigned int i = 0; i < msgthread_num; i++) {
        int rc = iop_thread_create(&pthread_msg[i], MsgProc, (void *) this, 0);
		if( rc == 0 ){
			iop_usleep(10);
#ifdef _DEBUG_INFO_
			cout << "Msg Thread start successfully" << endl;
#endif
		} else {
			isStarted = false;
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
			isStarted = false;
		}
	}

	for (unsigned int i = 0; i < recvthread_num; i++) {
        int rc = iop_thread_create(&pthread_recv[i], RecvProc, (void *) this, 0);
		if (0 == rc) {
			iop_usleep(10);
#ifdef _DEBUG_INFO_
			cout << "Recv Thread start successfully " << endl;
#endif
		} else {
			isStarted = false;
		}
	}



	return isStarted;
}

bool CServer::Stop(void) {
    if (isRunning()) {
		isStarted = false;
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
	return true;
}

DWORD CServer::MsgHandler(TS_PEER_MESSAGE& pmsg) {
    (void) pmsg;
	return 0;
}

void CServer::sendProc() {
	TS_PEER_MESSAGE pmsg;
	memset(&pmsg, 0, sizeof(TS_PEER_MESSAGE));

	CPeerConnection* peer = new CPeerConnection(pConnect->getSocket());

	while (isRunning()) {
		ReadOut(pmsg);
		peer->setPeer(pmsg.peeraddr);
		peer->send(pmsg.msg.Body, packetSize(pmsg.msg));

#ifdef _DEBUG_INFO_
		cout << "port:" << pConnect->getPeer()->sin_port << endl;
#endif
	}
	delete peer;
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
	
	CPeerConnection* peer = new CPeerConnection(pConnect->getSocket());

	while (isRunning()) {
		memset(&pmsg, 0, sizeof(TS_PEER_MESSAGE));
		if (peer->recv(pmsg.msg.Body, msglen) > 0) {
			memcpy(&pmsg.peeraddr, peer->getRecvAddr(), CAbsSocket::m_LocalAddrSize);
			WriteIn(pmsg);
		}
	}
#ifdef _DEBUG_INFO_
	cout << "recv thread exit" << endl;
#endif
	delete peer;
}
