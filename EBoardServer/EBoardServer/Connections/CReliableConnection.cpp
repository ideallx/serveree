#include <iostream>

#include "CReliableConnection.h"
#include "../DataUnit/CMessage.h"

using namespace std;

CReliableConnection::CReliableConnection() :
	bm(new CBlockManager()),
	needCacheSend(false),
	msgQueue(new TSQueue<ts_msg>),
	selfUid(ServerUID) {
	semMsg = CreateSemaphore(NULL, 0, 1024, NULL);
}

CReliableConnection::~CReliableConnection() {
	pthread_cancel(msgScan);
	pthread_cancel(msgIn);

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
		cout << "Scan Thread start successfully" << endl;
	} else {
		cout << "Scan Thread start failed " << endl;
		return false;
	}

	rc = pthread_create(&msgIn, NULL, MsgInProc, (void*) this);
	if (0 == rc) {
		iop_usleep(10);
		cout << "MsgIn Thread start successfully" << endl;
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

	msgQueue->enQueue(*msg);			// queue���Լ������������Բ��õ���msg����������
	ReleaseSemaphore(semMsg, 1, NULL);	// �ź����ſ�������msgIn Proc
	return result;
}

int CReliableConnection::send(const char* buf, ULONG len) {
	ts_msg *msg = (ts_msg*) buf;
	if (needCacheSend) {
		bm->record(*msg, packetSize(*msg));
	}

	return CHubConnection::send(buf, len);
}

static int lastMissing = 0;
void CReliableConnection::scanProcess() {
	if (NULL == bm)
		return;
	
	map<TS_UINT64, set<TS_UINT64> > results = bm->getLostSeqIDs();
	for (auto uidIter = results.begin(); uidIter != results.end(); uidIter++) { 	// ɨ������UID
		TS_UINT64 uid = uidIter->first;
		set<TS_UINT64> pids = uidIter->second;
		requestForResend(uid, pids);

		cout << uid << " missing:";
		for (auto i = pids.begin(); i != pids.end(); i++) 
			cout << " " << *i;
		cout << endl;
		lastMissing = pids.size();
	}
}

int CReliableConnection::send2Peer(ts_msg& msg) {
	CPeerConnection *peer = findPeer(getUid(msg));
	if (NULL == peer)
		return -1;
	return peer->send(msg.Body, packetSize(msg));
}

int CReliableConnection::send2Peer(ts_msg& msg, TS_UINT64 uid) {
	CPeerConnection *peer = findPeer(uid);
	if (NULL == peer)
		return -1;
	return peer->send(msg.Body, packetSize(msg));
}

int CReliableConnection::requestForResend(TS_UINT64 uid, set<TS_UINT64> pids) {
	if (pids.size() == 0)
		return 0;
	int result = 0;				
	auto iter = pids.begin();			// �ܹ�����ȥ������

	ts_msg *buffer = new ts_msg();
	RCONNECT* r = (RCONNECT*) buffer;

	r->head.type = RESEND;
	r->head.UID = selfUid;				// �Լ���UID
	r->head.sequence = 12;				// ��ŷ�0����
	int total = pids.size();			// �ܹ���Ҫ��������

	while (total > 0) {
		if (total < MaxSeqsInOnePacket)	// ÿ���������20������
			r->count = total;
		else
			r->count = MaxSeqsInOnePacket;
		total -= r->count;
		r->head.size = r->count * sizeof(TS_UINT64) + sizeof(TS_MESSAGE_HEAD);

		int count = 0;
		while (count < r->count) {
			r->seq[count++] = *iter++;
		}
		result += (send2Peer(*buffer, uid) > 0);
	}

	cout << "resend: " << result << endl;
	delete buffer;
	return result;
}

int CReliableConnection::resend(ts_msg& requestMsg) {
	int count = 0;
	RCONNECT* r = (RCONNECT*) &requestMsg;
	TS_UINT64 uid = r->head.UID;		// ���󷽵�UID

	CPeerConnection *peer = findPeer(uid);
	if (NULL == peer)
		return -1;

	ts_msg *p = new ts_msg();
	for (int i = 0; i < r->count; i++) {	
		if (ServerUID == uid) {
			uid = selfUid;				// ����Server��������Լ��ģ�����client������Server������uid��
		}
		if (bm->readRecord(uid, r->seq[i], *p) < 0)	// �����������󣬷�������
			continue;
		if (peer->send(p->Body, packetSize(*p)) > 0)
			count++;
	}

	delete p;
	return count;
}

void CReliableConnection::saveUserBlock(TS_UINT64 uid) {
	bm->saveBlock(uid);
	bm->removeBlock(uid);
}

// ���ھͼ��һ��seq���������ȫ�������������
bool CReliableConnection::validityCheck(ts_msg& msg) {
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
			conn->resend(*msg);
		} else {										// �����յ����������򱣴棬֮�����ϲ㴦��
			if (NULL == conn->bm)
				continue;
			conn->bm->record(*msg, packetSize(*msg));	// �����¼
		}
	}
	delete msg;
}