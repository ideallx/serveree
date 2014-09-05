#include <iostream>
#include <string>
#include "CReliableConnection.h"
#include "../DataUnit/CMessage.h"

using namespace std;

CReliableConnection::CReliableConnection() :
	bm(new CBlockManager()),			
	msgQueue(new TSQueue<ts_msg>),		// ��Ϣ���У������շ�
	selfUid(ServerUID),					// Ĭ��Ϊ������UID��client��ʱ��ҪsetUID()
	totalMiss(0),						// 
	totalMsgs(1),						// ��ֹ��0����
	fileNamePrefix("L") {						
	semMsg = CreateSemaphore(NULL, 0, 1024, NULL);
	semSave = CreateSemaphore(NULL, 0, 1024, NULL);
	createdBlock.clear();
}

CReliableConnection::~CReliableConnection() {
	pthread_cancel(msgScan);
	pthread_cancel(msgIn);

	CloseHandle(semMsg);
	CloseHandle(semSave);

	delete msgQueue;
	delete bm;
}

// ���˻����Ŀ��˿�֮�⣬��Ҫ����һ��ɨ���̣߳�һ����Ϣ�����߳�
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
	} else {
		cout << "MsgIn Thread start failed " << endl;
		return false;
	}

	rc = pthread_create(&msgSave, NULL, SaveProc, (void*) this);
	if (0 == rc) {
		iop_usleep(10);
		cout << "MsgSave Thread start successfully" << endl;
		return true;
	} else {
		cout << "MsgSave Thread start failed " << endl;
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
	case RESENDALL:
	case RESENDSERIES:
		result = -1;
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
		if (selfUid != ServerUID) {								// client�����⴦��
			bm->record(*msg);									// client����Ҫ��¼�����İ�

			if ((seq % 5 == 0) && missed.count(seq) == 0) 	{	// ����������Ȼ�������ش����ڶ�������������
				missed.insert(seq);
				// cout << uid << " missed " << seq << endl;
				return -1;
			}
			return CHubConnection::send(buf, len);
		} else {
			return CHubConnection::sendExcept(buf, len, getUid(*msg));
		}
	}
}

void CReliableConnection::scanProcess() {
	map<TS_UINT64, set<TS_UINT64> > results = bm->getLostSeqIDs();				// blockManager����
	for (auto uidIter = results.begin(); uidIter != results.end(); uidIter++) { // ɨ������UID
		TS_UINT64 uid = uidIter->first;											// block��
		set<TS_UINT64> pids = uidIter->second;									// package��
		requestForResend(uid, pids);
		totalMiss += pids.size();
		//cout << uid << " missing:";
		//for (auto iter = pids.begin(); iter != pids.end(); iter++) {
		//	cout << *iter;
		//}
		//cout << endl;
		// cout << "Missing Rate: " << getMissingRate() << endl;
	}
	set<pair<TS_UINT64, CPackage*> > sets;
	bm->getSavePackage(sets);
	for (auto iter = sets.begin(); iter != sets.end(); iter++) {
		saveQueue.enQueue(*iter);
		ReleaseSemaphore(semSave, 1, NULL);
		// cout << iter->first << " added to queue" << endl;
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
	file.second->save(fileNamePrefix + "_" + int2string(file.first) + ".zip", isFirst);
	//cout << "Missing Rate: " << getMissingRate() << endl;
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
	int result = 0;				
	auto iter = pids.begin();			// �ܹ�����ȥ������

	RCONNECT* r = new RCONNECT();

	r->head.type = RESEND;
	r->head.UID = selfUid;				// �Լ���UID
	r->head.sequence = 12;				// ��ŷ�0����
	int total = pids.size();			// �ܹ���Ҫ��������

	while (total > 0) {
		if (total < MaxSeqsInOnePacket)	// ÿ���������50������
			r->count = total;
		else
			r->count = MaxSeqsInOnePacket;
		total -= r->count;
		r->head.size = r->count * sizeof(TS_UINT64) + sizeof(TS_MESSAGE_HEAD);

		int count = 0;
		while (count < r->count) {
			r->seq[count++] = *iter++;
		}
		result += (send2Peer(*(ts_msg*) r, uid) > 0);
	}

	// cout << "resend: " << result << endl;
	delete r;
	return result;
}

int CReliableConnection::resend(ts_msg& requestMsg) {
	int count = 0;
	RCONNECT* r = (RCONNECT*) &requestMsg;
	TS_UINT64 uid = r->head.UID;					// ���󷽵�UID

	CPeerConnection *peer = findPeer(uid);			// ���󷽵ĵ�ַ
	if (NULL == peer)
		return -1;

	ts_msg *p = new ts_msg();
	for (int i = 0; i < r->count; i++) {	
		if (ServerUID == uid) {
			uid = selfUid;							// ����Server��������Լ��ģ�����client������Server������uid��
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

void CReliableConnection::receive(ts_msg& msg) {
	WaitForSingleObject(semMsg, INFINITE);
	if (!msgQueue->deQueue(msg))
		return;


	if (!validityCheck(msg))				// ��Ч�Լ��
		return;
	
	// cout << selfUid << ":received " << getSeq(msg) << endl;
	switch (getType(msg)) {
	case RESEND:							// �����յ��ش������Լ�����
		resend(msg);
		break;
	case RESENDALL:							// �¼�����õģ�����ȫ���ش�
		resendAll(getUid(msg));
		break;
	case RESENDSERIES: 						// ����ĳ��UID�Ĳ��������ش�
		{
			UP_RESEND_SERIES* upcmd = (UP_RESEND_SERIES*) &msg;
			resendPart(getUid(msg), upcmd->uid, upcmd->beginSeq, upcmd->endSeq);
		}
		break;
	default:								// �����յ��ش������Լ�����
		bm->record(msg);					// �����¼
		if (selfUid == ServerUID) {			// Serverת��
			send(msg.Body, packetSize(msg));
		}
		break;
	}
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

int CReliableConnection::resendAll(TS_UINT64 toUID) {
	CPeerConnection *peer = findPeer(toUID);
	if (NULL == peer)
		return -1;

	set<ts_msg*> msgs;
	bm->getAllMsgs(msgs);
	int count = 0;
	for (auto iter = msgs.begin(); iter != msgs.end(); iter++) {
		if (peer->send((**iter).Body, packetSize(**iter)) > 0) {
			count++;
		}
	}
	return count;
}

int CReliableConnection::resendPart(TS_UINT64 toUID, TS_UINT64 needUID, 
	TS_UINT64 fromSeq, TS_UINT64 toSeq) {

	CPeerConnection *peer = findPeer(toUID);
	if (NULL == peer)
		return -1;
	
	set<ts_msg*> msgs;
	bm->getMsgsFromUID(msgs, needUID, fromSeq, toSeq);				// ��ȡ����Ĳ���msgȻ����
	int count = 0;
	for (auto iter = msgs.begin(); iter != msgs.end(); iter++) {
		if (peer->send((**iter).Body, packetSize(**iter)) > 0) {
			count++;
		}
	}
	return count;
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
		conn->receive(*msg);
	}
	delete msg;
}

void* SaveProc(LPVOID lpParam) {
	pthread_detach(pthread_self());
	CReliableConnection* conn = (CReliableConnection*) lpParam;
	if (!conn) {
		return 0;
	}
	while (true) {
		conn->saveProcess();
	}
	return 0;
}
