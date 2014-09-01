#include "DWSClient.h"
#include "../Connections/CReliableConnection.h"

int DWSClient::clientUid = 100;

DWSClient::DWSClient(TS_UINT64 classid, TS_UINT64 reserved) :
	_classid(classid),
	_reserved(reserved),
	seq(0),
	_uid(clientUid) {
	dynamic_cast<CReliableConnection*> (pConnect)->setUID(_uid);
	clientUid++;
}

DWSClient::~DWSClient() {

}

void DWSClient::recvProc() {
	ULONG msglen = sizeof(ts_msg);
	TS_PEER_MESSAGE *pmsg = new TS_PEER_MESSAGE();
	memset(pmsg, 0, sizeof(TS_PEER_MESSAGE));
	
	while (isRunning()) {
		pConnect->recv(pmsg->msg.Body, msglen);
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

void DWSClient::sendProc() {
	TS_PEER_MESSAGE *pmsg = new TS_PEER_MESSAGE();
	memset(pmsg, 0, sizeof(TS_PEER_MESSAGE));

	while (isRunning()) {
		ReadOut(*pmsg);
		pConnect->send(pmsg->msg.Body, packetSize(pmsg->msg));
	}
	delete pmsg;
	cout << "send thread exit" << endl;
}

// 生成测试数据
void DWSClient::generateData() {
	TS_PEER_MESSAGE *msg = new TS_PEER_MESSAGE();

	if (seq > 200000)
		return;

	int length = rand() % 500 + 525;
	TS_MESSAGE_HEAD* head = (TS_MESSAGE_HEAD*) &msg->msg;
	head->size = length;
	head->sequence = ++seq;
	head->isEnd = 0;
	head->UID = _uid;
	head->version = 100;
	
	WriteOut(*msg);
	iop_usleep(1);			// 时间间隔
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
	pConnect->setPeer(addr);

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
		if (rc == 0) {
			iop_usleep(10);
			cout << "Msg Thread start successfully" << endl;
		} else {
			turnOff();
		}
	}

	pthread_t pthread_gen;
	int rc = pthread_create(&pthread_gen, NULL, GenProc, (void*) this);
	if (0 == rc) {
		iop_usleep(10);
		cout << "Data Generate Thread start successfully " << endl;
	} else {
		turnOff();
	}

	return isRunning();
}

void* GenProc(LPVOID lpParam) {
	pthread_detach(pthread_self());
	DWSClient* c = (DWSClient*) lpParam;
	if (!c) {
		return 0;
	}
	while (true) {
		c->generateData();		// 生成包
	}
	return 0;
}