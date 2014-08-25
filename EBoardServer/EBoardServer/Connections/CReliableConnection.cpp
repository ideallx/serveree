#include <iostream>

#include "CReliableConnection.h"
#include "../DataUnit/CMessage.h"

using namespace std;

CReliableConnection::CReliableConnection() :
	bm(new CBlockManager()),
	needCacheSend(false),
	msgQueue(new TSQueue<ts_msg>) {
	// sem_init((sem_t*) &semMsg, 0, 0);
	semMsg = CreateSemaphore(NULL, 0, 1024, NULL);
}

CReliableConnection::~CReliableConnection() {
	//pthread_cancel(msgScan);
	//pthread_cancel(msgIn);
	//sem_destroy((sem_t*) &semMsg);
	CloseHandle(semMsg);
	delete msgQueue;
	delete bm;
}

bool CReliableConnection::create(unsigned short localport) {
	if (!CHubConnection::create(localport))
		return false;

	int rc = pthread_create(&msgScan, NULL, ScanProc, (void*) this);
	if (0 == rc) {
		iop_usleep(10);
		cout << "Scan Thread start successfully " << endl;
	} else {
		cout << "Scan Thread start failed " << endl;
		return false;
	}

	rc = pthread_create(&msgIn, NULL, MsgInProc, (void*) this);
	if (0 == rc) {
		iop_usleep(10);
		cout << "MsgIn Thread start successfully " << endl;
		return true;
	} else {
		cout << "MsgIn Thread start failed " << endl;
		return false;
	}
}

int CReliableConnection::recv(char* buf, ULONG& len) {
	int result = CHubConnection::recv(buf, len);
	if (result <= 0)
		return result;

	ts_msg* msg = (ts_msg*) buf;
	if (RESEND == getType(*msg)) {		// �����յ��ش����󣬷���-1
		result = -1;
	}

	msgQueue->enQueue(*msg);				// queue���Լ������������Բ��õ���msg����������
	
	//sem_post((sem_t*) &semMsg);			// �ź����ſ�������msgIn Proc
	ReleaseSemaphore(semMsg, 1, NULL);
	return result;
}

int CReliableConnection::send(const char* buf, ULONG len) {
	int result = CHubConnection::send(buf, len);
	if (result <= 0)
		return result;
	
	if (needCacheSend) {
		ts_msg *msg = (ts_msg*) buf;
		bm->record(*msg, packetSize(*msg));
	}

	return result;
}

static int lastMissing = 0;
void CReliableConnection::scanProcess() {
	if (NULL == bm)
		return;
	
	map<TS_UINT64, set<TS_UINT64> > results = bm->getLostSeqIDs();
	for (auto uidIter = results.begin(); uidIter != results.end(); uidIter++) {		// ɨ������UID
		TS_UINT64 uid = (*uidIter).first;
		set<TS_UINT64> pids = (*uidIter).second;
		resendForSelfLost(uid, pids);

		if (lastMissing != pids.size()) {
			cout << "missing: " << pids.size() << endl;
			lastMissing = pids.size();
		}
	}
}

int CReliableConnection::send2Peer(ts_msg& msg) {
	CPeerConnection *peer = findPeer(getUid(msg));
	if (NULL == peer)
		return -1;

	return peer->send(msg.Body, packetSize(msg));
}

int CReliableConnection::resendForSelfLost(TS_UINT64 uid, set<TS_UINT64> pids) {
	if (pids.size() == 0)
		return 0;
	int result = 0;				

	auto iter = pids.begin();			// �ܹ�����ȥ������

	ts_msg *p = new ts_msg();

	TS_MESSAGE_HEAD* head = (TS_MESSAGE_HEAD*) p;
	RCONNECT* r = (RCONNECT*) ((char *) p + sizeof(TS_MESSAGE_HEAD));

	head->type = RESEND;
	head->UID = 100;
	head->sequence = ~0;
	int size = pids.size();				// �ܹ���Ҫ��������

	while (size > 0) {
		if (size < MaxSeqsInOnePacket)	// ÿ���������20������
			r->size = size;
		else
			r->size = MaxSeqsInOnePacket;
		size -= r->size;
		head->size = r->size * sizeof(TS_UINT64) + sizeof(TS_MESSAGE_HEAD);
		int count = 0;
		while (count < r->size) {
			r->seq[count++] = *iter;
			iter++;
		}
		result += (send2Peer(*p) > 0);
	}

	cout << "resend: " << result << endl;
	delete p;
	return result;
}

int CReliableConnection::resendForOthersLost(ts_msg& msg) {
	TS_UINT64 uid = getUid(msg);

	int count = 0;
	ts_msg *p = new ts_msg();
	RCONNECT* r = (RCONNECT*) ((char *) &msg + sizeof(TS_MESSAGE_HEAD));

	for (int i = 0; i < r->size; i++) {
		if (!bm->readRecord(uid, r->seq[i], *p))	// �����������󣬷�������
			continue;
		if (send2Peer(*p) > 0)
			count ++;
	}
	delete p;
	return count;
}

void CReliableConnection::saveUserBlock(TS_UINT64 uid) {
	bm->saveBlock(uid);
	bm->removeBlock(uid);
}

// ���ھͼ��һ��seq�����������������������
static set<TS_UINT64> msgs;
bool CReliableConnection::validityCheck(ts_msg& msg) {
	// cout << getSeq(msg) << endl;
	if (getSeq(msg) == 0)
		return false;

	return true;
}

void* ScanProc(LPVOID lpParam) {
	pthread_detach(pthread_self());
	CReliableConnection* conn = (CReliableConnection*) lpParam;
	if (!conn) {
		return 0;
	}
	while (true) {
		conn->scanProcess();	// ɨ������ط�
		iop_usleep(100);		// ʱ����
	}
	return 0;
}

void* MsgInProc(LPVOID lpParam) {
	pthread_detach(pthread_self());
	CReliableConnection* conn = (CReliableConnection*) lpParam;
	if (!conn) {
		return 0;
	}
	ts_msg* msg = new ts_msg();
	while (true) {
		WaitForSingleObject(conn->semMsg, INFINITE);
		//sem_wait((sem_t*) &conn->semMsg);
		if (!conn->msgQueue->deQueue(*msg))
			continue;

		if (!conn->validityCheck(*msg))
			continue;
		
		if (RESEND == getType(*msg)) {					// �����յ��ش������Լ�����
			conn->resendForOthersLost(*msg);
		} else {										// �����յ����������򱣴棬֮�����ϲ㴦��
			if (NULL == conn->bm)
				continue;
			conn->bm->record(*msg, packetSize(*msg));	// �����¼
		}
	}
	delete msg;
}