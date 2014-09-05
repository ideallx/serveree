#include <iostream>
#include <string>
#include "CReliableConnection.h"
#include "../DataUnit/CMessage.h"

using namespace std;

CReliableConnection::CReliableConnection() :
	bm(new CBlockManager()),			
	msgQueue(new TSQueue<ts_msg>),		// 消息队列，处理收发
	selfUid(ServerUID),					// 默认为服务器UID，client端时需要setUID()
	totalMiss(0),						// 
	totalMsgs(1),						// 防止除0错误
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

// 除了基本的开端口之外，还要增加一个扫描线程，一个消息处理线程
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

	msgQueue->enQueue(*msg);			// queue会自己作副本，所以不用担心msg的生命周期
	ReleaseSemaphore(semMsg, 1, NULL);	// 信号量放开，交给msgIn Proc
	return result;
}

int CReliableConnection::send(const char* buf, ULONG len) {
	ts_msg *msg = (ts_msg*) buf;
	TS_UINT64 seq = getSeq(*msg);

	if (seq != 0) {												// seq为0，控制类指令，暂不保存
		if (selfUid != ServerUID) {								// client端特殊处理
			bm->record(*msg);									// client端需要记录发出的包

			if ((seq % 5 == 0) && missed.count(seq) == 0) 	{	// 故意抛弃，然后请求重传，第二次来正常接收
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
	map<TS_UINT64, set<TS_UINT64> > results = bm->getLostSeqIDs();				// blockManager层找
	for (auto uidIter = results.begin(); uidIter != results.end(); uidIter++) { // 扫描所有UID
		TS_UINT64 uid = uidIter->first;											// block层
		set<TS_UINT64> pids = uidIter->second;									// package层
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
	auto iter = pids.begin();			// 总共发出去的条数

	RCONNECT* r = new RCONNECT();

	r->head.type = RESEND;
	r->head.UID = selfUid;				// 自己的UID
	r->head.sequence = 12;				// 序号非0即可
	int total = pids.size();			// 总共需要发的条数

	while (total > 0) {
		if (total < MaxSeqsInOnePacket)	// 每条报文最多50个请求
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
	TS_UINT64 uid = r->head.UID;					// 请求方的UID

	CPeerConnection *peer = findPeer(uid);			// 请求方的地址
	if (NULL == peer)
		return -1;

	ts_msg *p = new ts_msg();
	for (int i = 0; i < r->count; i++) {	
		if (ServerUID == uid) {
			uid = selfUid;							// 若是Server请求，则读自己的，若是client请求，则Server读各个uid的
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

void CReliableConnection::receive(ts_msg& msg) {
	WaitForSingleObject(semMsg, INFINITE);
	if (!msgQueue->deQueue(msg))
		return;


	if (!validityCheck(msg))				// 有效性检测
		return;
	
	// cout << selfUid << ":received " << getSeq(msg) << endl;
	switch (getType(msg)) {
	case RESEND:							// 若是收到重传请求，自己处理
		resend(msg);
		break;
	case RESENDALL:							// 新加入课堂的，请求全部重传
		resendAll(getUid(msg));
		break;
	case RESENDSERIES: 						// 请求某个UID的部分数据重传
		{
			UP_RESEND_SERIES* upcmd = (UP_RESEND_SERIES*) &msg;
			resendPart(getUid(msg), upcmd->uid, upcmd->beginSeq, upcmd->endSeq);
		}
		break;
	default:								// 若是收到重传请求，自己处理
		bm->record(msg);					// 缓存记录
		if (selfUid == ServerUID) {			// Server转发
			send(msg.Body, packetSize(msg));
		}
		break;
	}
}

// 现在就检查一下seq，后续检查全加入这个函数中
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
	bm->getMsgsFromUID(msgs, needUID, fromSeq, toSeq);				// 获取需求的部分msg然后发送
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
