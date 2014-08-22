#include "CServer.h"
#include "../Connections/CReliableConnection.h"

CServer::CServer() :
	MsgLen(MESSAGE_SIZE),

	recvthread_num(5),
	sendthread_num(2),
	msgthread_num(1),

	pthread_recv(new pthread_t[recvthread_num]),
	pthread_send(new pthread_t[sendthread_num]),
	pthread_msg(new pthread_t[msgthread_num]),

	p_InMsgQueue(new TSQueue<TS_PEER_MESSAGE>),
	p_OutMsgQueue(new TSQueue<TS_PEER_MESSAGE>) {

	Port = 0;
	pConnect = new CReliableConnection;

	//sem_init((sem_t*) &data_in, 0, 0);
	//sem_init((sem_t*) &data_out, 0, 0);
	data_in = CreateSemaphore(NULL, 0, 1024, NULL);
	data_out = CreateSemaphore(NULL, 0, 1024, NULL);

	time_t t;
	srand((unsigned) time(&t));
	struct timeval tv;
	gettimeofday(&tv, NULL);
	starttime = tv.tv_sec;
}

CServer::~CServer(void) {
	Stop();
	// sem_destroy((sem_t*) &data_in);
	// sem_destroy((sem_t*) &data_out);
	CloseHandle(data_in);
	CloseHandle(data_out);

	DESTROY(p_InMsgQueue);
	DESTROY(p_OutMsgQueue);
}

TS_UINT64 CServer::AllocateSessionID(void) {
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_sec;
}

bool CServer::Initialize(void) {
	return TRUE;
}

bool CServer::Uninitialize(void) {
	pConnect->clear();
	return TRUE;
}


void CServer::ReadIn(TS_PEER_MESSAGE& pmsg) {
	// sem_wait((sem_t*) &data_in);
	WaitForSingleObject(data_in, INFINITE);
	p_InMsgQueue->deQueue(pmsg);
}

void CServer::WriteIn(const TS_PEER_MESSAGE& pmsg) {
	p_InMsgQueue->enQueue(pmsg);
	// sem_post((sem_t*) &data_in);
	ReleaseSemaphore(data_in, 1, NULL);
}

void CServer::ReadOut(TS_PEER_MESSAGE& pmsg) {
	// sem_wait((sem_t*) &data_out);
	WaitForSingleObject(data_out, INFINITE);
	p_OutMsgQueue->deQueue(pmsg);
}

void CServer::WriteOut(const TS_PEER_MESSAGE& pmsg) {
	p_OutMsgQueue->enQueue(pmsg);
	// sem_post((sem_t*) &data_out);
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
		if( rc == 0 ){
			iop_usleep(10);
			cout << "Msg Thread start successfully" << endl;
		} else {
			turnOff();
		}
	}
	return isRunning();
}

bool CServer::Stop(void) {
	Uninitialize();
	turnOff();
	iop_usleep(1000);
	for (unsigned int i = 0; i < sendthread_num; i++) {
		pthread_cancel(pthread_send[i]);
	}
	for (unsigned int i = 0; i < recvthread_num; i++) {
		pthread_cancel(pthread_recv[i]);
	}
	for (unsigned int i = 0; i < msgthread_num; i++) {
		pthread_cancel(pthread_msg[i]);
	}
	delete[] pthread_send;
	delete[] pthread_recv;
	delete[] pthread_msg;
//	freeConn();
	iop_usleep(1000);
	return TRUE;
}

DWORD CServer::MsgHandler(TS_PEER_MESSAGE& pmsg) {	
	WriteOut(pmsg);
	return 0;
}