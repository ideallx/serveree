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
	if (RESEND == getType(*msg)) {		// 若是收到重传请求，返回-1
		result = -1;
	}

	msgQueue->enQueue(*msg);				// queue会自己作副本，所以不用担心msg的生命周期
	
	//sem_post((sem_t*) &semMsg);			// 信号量放开，交给msgIn Proc
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
	for (auto uidIter = results.begin(); uidIter != results.end(); uidIter++) {		// 扫描所有UID
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

	auto iter = pids.begin();			// 总共发出去的条数

	ts_msg *p = new ts_msg();

	TS_MESSAGE_HEAD* head = (TS_MESSAGE_HEAD*) p;
	RCONNECT* r = (RCONNECT*) ((char *) p + sizeof(TS_MESSAGE_HEAD));

	head->type = RESEND;
	head->UID = 100;
	head->sequence = ~0;
	int size = pids.size();				// 总共需要发的条数

	while (size > 0) {
		if (size < MaxSeqsInOnePacket)	// 每条报文最多20个请求
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
		if (!bm->readRecord(uid, r->seq[i], *p))	// 读到几条请求，发多少条
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

// 现在就检查一下seq，后续反正加入这个函数中
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
		conn->scanProcess();	// 扫描包并重发
		iop_usleep(100);		// 时间间隔
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
		
		if (RESEND == getType(*msg)) {					// 若是收到重传请求，自己处理
			conn->resendForOthersLost(*msg);
		} else {										// 若是收到正常请求，则保存，之后由上层处理
			if (NULL == conn->bm)
				continue;
			conn->bm->record(*msg, packetSize(*msg));	// 缓存记录
		}
	}
	delete msg;
}