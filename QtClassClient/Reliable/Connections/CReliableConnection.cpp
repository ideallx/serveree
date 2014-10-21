#include <iostream>
#include <string>
#include "CReliableConnection.h"
#include "../DataUnit/CMessage.h"
#include "../../Stdafx.h"

using namespace std;

CReliableConnection::CReliableConnection() :
	bm(new CBlockManager()),			
	msgQueue(new TSQueue<ts_msg>),		// ��Ϣ���У������շ�
	selfUid(ServerUID),					// Ĭ��Ϊ������UID��client��ʱ��ҪsetUID()
	totalMiss(0),						// 
	totalMsgs(1),						// ��ֹ��0����
	fileNamePrefix("L"),
	resendWhenAsk(true),
	isRunning(false) {						
	semMsg = CreateSemaphore(NULL, 0, 1024, NULL);
	semSave = CreateSemaphore(NULL, 0, 1024, NULL);
	needScan = CreateSemaphore(NULL, 0, 10, NULL);		// ���10����10�β��յ��µ�msg��scan�ٶȷŻ�
	createdBlock.clear();
}

CReliableConnection::~CReliableConnection() {
    if (isRunning) {
        isRunning = false;
        iop_usleep(10);
        pthread_cancel(msgScan);
        pthread_cancel(msgIn);
    }

	CloseHandle(semMsg);
	CloseHandle(semSave);
	CloseHandle(needScan);

	delete msgQueue;
	delete bm;
}

// ���˻����Ŀ��˿�֮�⣬��Ҫ����һ��ɨ���̣߳�һ����Ϣ�����߳�
bool CReliableConnection::create(unsigned short localport) {
	if (!CHubConnection::create(localport))
		return false;

	isRunning = true;

	int rc = pthread_create(&msgScan, NULL, ScanProc, (void*) this);
	if (0 == rc) {
		iop_usleep(10);
		cout << "Scan Thread start successfully" << endl;
	} else {
		cout << "Scan Thread start failed " << endl;
		isRunning = false;
		return false;
	}

	rc = pthread_create(&msgIn, NULL, MsgInProc, (void*) this);
	if (0 == rc) {
		iop_usleep(10);
		cout << "MsgIn Thread start successfully" << endl;
	} else {
		cout << "MsgIn Thread start failed " << endl;
		isRunning = false;
		return false;
	}

	rc = pthread_create(&msgSave, NULL, SaveProc, (void*) this);
	if (0 == rc) {
		iop_usleep(10);
		cout << "MsgSave Thread start successfully" << endl;
		return true;
	} else {
		cout << "MsgSave Thread start failed " << endl;
		isRunning = false;
		return false;
	}
}

int CReliableConnection::recv(char* buf, ULONG& len) {
	int result = CHubConnection::recv(buf, len);
	if (result <= 0)
		return result;

	ts_msg* msg = (ts_msg*) buf;
	switch (getType(*msg)) {
	case RESEND:
		result = -1;
		if (false == resendWhenAsk)		// �����ط����󣡣����ط�
			return result;
		break;
	default:
		totalMsgs++;
		break;
	}

	msgQueue->enQueue(*msg);			// queue���Լ������������Բ��õ���msg����������
	ReleaseSemaphore(semMsg, 1, NULL);	// �ź����ſ�������msgIn Proc
	return result;
}

int CReliableConnection::send(const char* buf, ULONG len) {
	ts_msg *msg = (ts_msg*) buf;
	TS_UINT64 seq = getSeq(*msg);

	if (seq != 0) {												// seqΪ0��������ָ��ݲ�����
		if (selfUid != ServerUID) {								// client�����⴦��.
			bm->record(*msg);									// client����Ҫ��¼�����İ�
            send2Peer(*msg, ServerUID);
		} else {
			return CHubConnection::sendExcept(buf, len, getUid(*msg));
		}
	}
	return CHubConnection::send(buf, len);
}

void CReliableConnection::scanProcess() {
	// ɨ�趪�����ط�
	map<TS_UINT64, set<TS_UINT64> > results = bm->getLostSeqIDs();				// blockManager����
	for (auto uidIter = results.begin(); uidIter != results.end(); uidIter++) { // ɨ������UID
		TS_UINT64 uid = uidIter->first;											// block��
		set<TS_UINT64> pids = uidIter->second;									// package��
		requestForResend(uid, pids);
		totalMiss += pids.size();
	}

	// ɨ�豣������ӱ������
	set<pair<TS_UINT64, CPackage*> > sets;
	bm->getSavePackage(sets);
	for (auto iter = sets.begin(); iter != sets.end(); iter++) {
		saveQueue.enQueue(*iter);
		ReleaseSemaphore(semSave, 1, NULL);
	}
}

void CReliableConnection::saveProcess() {
	WaitForSingleObject(semSave, INFINITE);

	pair<TS_UINT64, CPackage*> file;
	if (!saveQueue.deQueue(file))
		return;

	bool isFirst = false;
	if (createdBlock.count(file.first) == 0) {
		createdBlock.insert(file.first);
		isFirst = true;
	}
	//cout << "3";
	file.second->save(fileNamePrefix + "_" + int2string(file.first) + ".zip", isFirst);
	cout << "Missing Rate: " << getMissingRate() << endl;
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
	// cout << "port:" << peer->getPeer()->sin_port << endl;
	return peer->send(msg.Body, packetSize(msg));
}

int CReliableConnection::requestForResend(TS_UINT64 uid, set<TS_UINT64> pids) {
	if (pids.size() == 0)
		return 0;

    cout << "ask for resend size is: " << pids.size() << endl;

	int result = 0;				
	auto iter = pids.begin();			// �ܹ�����ȥ������

	RCONNECT* r = new RCONNECT();

	r->head.type = RESEND;
	r->head.UID = selfUid;				// �Լ���UID
	r->head.sequence = 22121;			// ��ŷ�0����
	r->missingUID = uid;				// û�յ��İ�������UID
	r->missingType = MISS_SINGLE;		// ����һ�İ�
	int total = pids.size();			// �ܹ���Ҫ��������

	while (total > 0) {
		if (total < MaxSeqsInOnePacket)	// ÿ���������50������
			r->count = total;
		else
			r->count = MaxSeqsInOnePacket;
		total -= r->count;
		r->head.size = sizeof(RCONNECT);

		int count = 0;
		while (count < r->count) {
			r->seq[count++] = *iter++;
		}
		if (ServerUID == selfUid) {		// Server���ʸ����û�Ҫ
			result += (send2Peer(*(ts_msg*) r, uid) > 0);
		} else {						// client���ʿͻ���Ҫ
			result += (send2Peer(*(ts_msg*) r, ServerUID) > 0);
		}
	}

	// cout << "resend: " << result << endl;
	delete r;
	return result;
}

int CReliableConnection::resend(ts_msg& requestMsg) {
	int count = 0;
	RCONNECT* r = (RCONNECT*) &requestMsg;
	TS_UINT64 uid = r->head.UID;					// ���󷽵�UID
	TS_UINT64 missingUID = r->missingUID;			// ����������UID
	
	ts_msg *p = new ts_msg();
	if (ServerUID == uid) {
		uid = selfUid;								// ����Server��������Լ��ģ�����client������Server������uid��
	}

	if (r->missingType == MISS_SINGLE) {			// ����MISS�ش�
        CPeerConnection *peer = findPeer(uid);			// ���󷽵ĵ�ַ
        if (NULL == peer)
            return -1;

		for (int i = 0; i < r->count; i++) {
			if (bm->readRecord(missingUID, r->seq[i], *p) < 0)	// �����������󣬷�������
                continue;
			if (peer->send(p->Body, packetSize(*p)) > 0)
				count++;
		}
    } else if (r->missingType == MISS_SERIES) {		// ����MISS�ش�
        for (int i = 0; i < r->count / 2; i++) {	// ÿ����seqΪһ��
            resendPart(uid, r->missingUID, r->seq[i*2], r->seq[i*2 + 1]);
        }
	} else if (r->missingType == MISS_ALL) {		// ȫ���ش�
		resendAll(uid);
	}

	delete p;
	return count;
}

void CReliableConnection::saveUserBlock(TS_UINT64 uid) {
	bm->saveBlock(uid);
	// bm->removeBlock(uid);
}

void CReliableConnection::receive(ts_msg& msg) {
	if (!msgQueue->deQueue(msg))
		return;

	if (!validityCheck(msg))				// ��Ч�Լ��
		return;
	
	unsigned char type = getType(msg);
    switch (type) {
    case RESEND:                            // �����յ��ش������Լ�����
        resend(msg);
        break;
    default:                                // �����յ��ش������Լ�����
        bm->record(msg);					// �����¼
        if (selfUid == ServerUID) {			// Serverת��
            send(msg.Body, packetSize(msg));
        }
        break;
    }
	ReleaseSemaphore(needScan, 1, NULL);	// �յ�����msg����Ҫ����scan
}

// ���ھͼ��һ��seq���������ȫ�������������
bool CReliableConnection::validityCheck(ts_msg& msg) {
	if (getSeq(msg) == 0)
		return false;
	return true;
}

void CReliableConnection::setFilePrefix(string fprefix) { 
	fileNamePrefix = fprefix; 
	bm->setFilePrefix(fprefix);
}

int CReliableConnection::resendAll(TS_UINT64 uid) {
	CPeerConnection *peer = findPeer(uid);			// ���󷽵ĵ�ַ
	int count = 0;
	ts_msg p;

	iop_lock(&mutex_lock);
	for (auto iter = allUsers.begin(); iter != allUsers.end(); iter++) {
		TS_UINT64 uid = *iter;
		TS_UINT64 end = bm->getMaxSeqOfUID(uid);
		cout << "user: " << uid << " has " << end << " message" << endl;

		for (int j = 1; j <= end; j++) {
			if (bm->readRecord(uid, j, p) < 0)
				continue;
			if (peer->send(p.Body, packetSize(p)) > 0)
				count++;
		}
	}
	iop_unlock(&mutex_lock);
	cout << "resend all " << count << "message" << endl;
	return count;
}

int CReliableConnection::resendPart(TS_UINT64 toUID,
                                    TS_UINT64 needUID,
                                    TS_UINT64 fromSeq,
                                    TS_UINT64 toSeq) {

    CPeerConnection *peer = findPeer(toUID);			// ���󷽵ĵ�ַ
    if (NULL == peer)
        return -1;

    if (-1 == toSeq)							// seq��ֹ������-1����Ϊȫ������
        toSeq = bm->getMaxSeqOfUID(needUID);

    ts_msg p;
    int count = 0;
    for (TS_UINT64 j = fromSeq; j < toSeq; j++) {
        if (bm->readRecord(needUID, j, p) < 0)
            continue;
        if (peer->send(p.Body, packetSize(p)) > 0)
            count++;
    }
    return count;
}

int CReliableConnection::sendLastMsg() {
    TS_UINT64 max = bm->getMaxSeqOfUID(SelfUID);
    ts_msg p;
    bm->readRecord(SelfUID, max, p);
    return send2Peer(p, ServerUID);
}

void* ScanProc(LPVOID lpParam) {
	pthread_detach(pthread_self());
	CReliableConnection* conn = (CReliableConnection*) lpParam;
	if (!conn) {
		return 0;
	}
	while (conn->isRunning) {
        WaitForSingleObject(conn->needScan, 3000);	// ����1��
		conn->scanProcess();		// ɨ������ط�
		iop_usleep(100);			// ʱ����
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
	while (conn->isRunning) {
		WaitForSingleObject(conn->semMsg, INFINITE);
		conn->receive(*msg);
	}
	delete msg;
	return 0;
}

void* SaveProc(LPVOID lpParam) {
	pthread_detach(pthread_self());
	CReliableConnection* conn = (CReliableConnection*) lpParam;
	if (!conn) {
		return 0;
	}
	while (conn->isRunning) {
		conn->saveProcess();
	}
	return 0;
}
