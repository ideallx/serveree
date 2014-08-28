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
	if (RESEND == getType(*msg)) {		// 若是收到重传请求，返回-1
		result = -1;
	}

	msgQueue->enQueue(*msg);			// queue会自己作副本，所以不用担心msg的生命周期
	ReleaseSemaphore(semMsg, 1, NULL);	// 信号量放开，交给msgIn Proc
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
	for (auto uidIter = results.begin(); uidIter != results.end(); uidIter++) { 	// 扫描所有UID
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
	auto iter = pids.begin();			// 总共发出去的条数

	ts_msg *buffer = new ts_msg();
	RCONNECT* r = (RCONNECT*) buffer;

	r->head.type = RESEND;
	r->head.UID = selfUid;				// 自己的UID
	r->head.sequence = 12;				// 序号非0即可
	int total = pids.size();			// 总共需要发的条数

	while (total > 0) {
		if (total < MaxSeqsInOnePacket)	// 每条报文最多20个请求
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
	TS_UINT64 uid = r->head.UID;		// 请求方的UID

	CPeerConnection *peer = findPeer(uid);
	if (NULL == peer)
		return -1;

	ts_msg *p = new ts_msg();
	for (int i = 0; i < r->count; i++) {	
		if (ServerUID == uid) {
			uid = selfUid;				// 若是Server请求，则读自己的，若是client请求，则Server读各个uid的
		}
		if (bm->readRecord(uid, r->seq[i], *p) < 0)	// 读到几条请求，发多少条
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

// 现在就检查一下seq，后续检查全加入这个函数中
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
			conn->resend(*msg);
		} else {										// 若是收到正常请求，则保存，之后由上层处理
			if (NULL == conn->bm)
				continue;
			conn->bm->record(*msg, packetSize(*msg));	// 缓存记录
		}
	}
	delete msg;
}