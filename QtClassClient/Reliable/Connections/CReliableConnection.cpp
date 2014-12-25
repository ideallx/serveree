#include <iostream>
#include <string>
#include "CReliableConnection.h"
#include "../DataUnit/CMessage.h"
#include "../../Stdafx.h"
#include "../Strategy/CSettings.h"

using namespace std;

const int minScanInterval = 30;
const int maxScanInterval = 1000;

thread_ret_type thread_func_call ScanProc(LPVOID lpParam) {
    iop_thread_detach_self();
    CReliableConnection* conn = reinterpret_cast<CReliableConnection*> (lpParam);
    if (!conn) {
        iop_thread_exit(0);
        return 0;
    }

    conn->scanProcess();		// ɨ������ط�
#ifdef _DEBUG_INFO_
    cout << "ScanProc exit" << endl;
#endif
    iop_thread_exit(0);
    return 0;
}

thread_ret_type thread_func_call MsgInProc(LPVOID lpParam) {
    iop_thread_detach_self();
    CReliableConnection* conn = reinterpret_cast<CReliableConnection*> (lpParam);
    if (!conn) {
        iop_thread_exit(0);
        return 0;
    }

    conn->receive();
#ifdef _DEBUG_INFO_
    cout << "MsgInProc exit" << endl;
#endif
    iop_thread_exit(0);
    return 0;
}

thread_ret_type thread_func_call SaveProc(LPVOID lpParam) {
    iop_thread_detach_self();
    CReliableConnection* conn = reinterpret_cast<CReliableConnection*> (lpParam);
    if (!conn) {
        iop_thread_exit(0);
        return 0;
    }

    conn->saveProcess();
#ifdef _DEBUG_INFO_
    cout << "SaveProc exit" << endl;
#endif
    iop_thread_exit(0);
    return 0;
}

CReliableConnection::CReliableConnection()
	: bm(new CBlockManager())			
	, msgQueue(new TSQueue<ts_msg>)		// ��Ϣ���У������շ�
	, selfUid(ServerUID)				// Ĭ��Ϊ������UID��client��ʱ��ҪsetUID()
	, totalMiss(0)						// 
    , totalMsgs(0)
	, phaseMsgs(0)
    , totalMsgsOfClass(-1)              // ���Ա���Ƿ��յ��������б�
	, fileNamePrefix("L")
	, resendWhenAsk(true)
    , isRunning(false)
    , requestCount(0)
	, lastMissing(-1)
	, lastUserNum(-1) {
    semMsg = CreateSemaphore(NULL, 0, 102400, NULL);
    semSave = CreateSemaphore(NULL, 0, 102400, NULL);
	needScan = CreateSemaphore(NULL, 0, 10, NULL);		// ���10����10�β��յ��µ�msg��scan�ٶȷŻ�
	createdBlock.clear();

	iop_lock_init(&ioLock);
}

CReliableConnection::~CReliableConnection() {
	delete bm;
    if (isRunning) {
        isRunning = false;
        iop_usleep(200);
		iop_thread_cancel(pthread_input);
		iop_thread_cancel(pthread_scan);
		iop_thread_cancel(pthread_save);
    }

	iop_lock_destroy(&ioLock);
	CloseHandle(semMsg);
	CloseHandle(semSave);
	CloseHandle(needScan);
    pSocket->closeSocket();

	delete msgQueue;
}

// ���˻����Ŀ��˿�֮�⣬��Ҫ����һ��ɨ���̣߳�һ����Ϣ�����߳�
bool CReliableConnection::create(unsigned short localport) {
	if (!CHubConnection::create(localport)) {
		return false;
	}

	isRunning = true;

    int rc = iop_thread_create(&pthread_scan, ScanProc, (void *) this, 0);
	if (0 == rc) {
		iop_usleep(10);
#ifdef _DEBUG_INFO_
		cout << "Scan Thread start successfully" << endl;
#endif
	} else {
		cout << "Scan Thread start failed " << endl;
		isRunning = false;
		return false;
	}

    rc = iop_thread_create(&pthread_input, MsgInProc, (void *) this, 0);
	if (0 == rc) {
		iop_usleep(10);
#ifdef _DEBUG_INFO_
		cout << "MsgIn Thread start successfully" << endl;
#endif
	} else {
		iop_thread_cancel(pthread_scan);
		cout << "MsgIn Thread start failed " << endl;
		isRunning = false;
		return false;
	}

    rc = iop_thread_create(&pthread_save, SaveProc, (void *) this, 0);
	if (0 == rc) {
		iop_usleep(10);
#ifdef _DEBUG_INFO_
		cout << "MsgSave Thread start successfully" << endl;
#endif
		return true;
	} else {
		iop_thread_cancel(pthread_scan);
		iop_thread_cancel(pthread_input);
		cout << "MsgSave Thread start failed " << endl;
		isRunning = false;
		return false;
	}
}


void CReliableConnection::receive() {
    ts_msg msg;
    while (isRunning) {
        WaitForSingleObject(semMsg, INFINITE);

        if (!msgQueue->deQueue(msg))
            continue;

        if (!validityCheck(msg))				// ��Ч�Լ��
            continue;

        unsigned char type = getType(msg);
        switch (type) {
        case RESEND:                            // �����յ��ش������Լ�����
            resend(msg);
            break;
        case MAXSEQLIST:
            requestForSeriesResend(msg);
            break;
        case CONNECTION:
            break;
        default:                                // �����յ��ش������Լ�����
            if (bm->record(msg) > 0) {			// �����¼
                totalMsgs++;
            }
            break;
        }
        ReleaseSemaphore(needScan, 1, NULL);	// �յ�����msg����Ҫ����scan
    }
}

int CReliableConnection::recv(char* buf, ULONG& len) {
	int result = CHubConnection::recv(buf, len);
	if (result <= 0)
		return result;

    ts_msg* msg = (ts_msg*) buf;

    if (!validityCheck(*msg))				// ��Ч�Լ��
        return -1;

    TS_MESSAGE_HEAD* head = (TS_MESSAGE_HEAD*) msg;

  //  if ((selfUid == ServerUID) && (peerHub->count(head->UID) == 0))		// make sure the message was sent by logged in user
		//return -1;

	switch (head->type) {
    case RESEND:
        result = -1;
#ifdef _DEBUG_INFO_
		cout << "resend" << endl;
#endif
		if (false == resendWhenAsk)		// �����ط����󣡣����ط�
            return result;
        resend(*msg);
        break;
    case MAXSEQLIST:
        requestForSeriesResend(*msg);
        result = -1;
        break;
    case CONNECTION:
        break;
    default:
        if (selfUid == ServerUID) {			// Serverת��
            send(msg->Body, packetSize(*msg));
        }

        if (bm->record(*msg) > 0) {			// �����¼
            totalMsgs++;
        }
		break;
	}

//	msgQueue->enQueue(*msg);			// queue���Լ������������Բ��õ���msg����������
//	ReleaseSemaphore(semMsg, 1, NULL);	// �ź����ſ�������msgIn Proc
	return result;
}

int CReliableConnection::send(const char* buf, ULONG len, TS_UINT64 uid) {
	ts_msg *msg = (ts_msg*) buf;
	TS_UINT64 seq = getSeq(*msg);

    // hub::send is same to send2peer uid in client mode for peerhub of hub is only server inside
	if (seq != 0) {												// seqΪ0��������ָ��ݲ�����
        if (selfUid != ServerUID) {								// client�����⴦��.
			iop_lock(&ioLock);
			bm->record(*msg);									// client����Ҫ��¼�����İ�
			iop_unlock(&ioLock);
            return send2Peer(*msg, uid);
		} else {
			return CHubConnection::sendExcept(buf, len, getUid(*msg));
		}
	} else {
		return CHubConnection::send(buf, len);
	}
}

void CReliableConnection::scanProcess() {
    while (isRunning) {
        WaitForSingleObject(needScan, maxScanInterval);	// ����2��
        // ɨ�趪�����ط�
        totalMiss = 0;
        map<TS_UINT64, set<TS_UINT64> > results;
		bm->getLostSeqIDs(results);						// blockManager����
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

		if (0 != totalMiss && lastMissing != totalMiss) {
			cout << "missing: " << totalMiss << " first is " << *(results.begin()->second.begin()) << endl;
		}
		lastMissing = totalMiss;

		phaseMsgs = totalMsgs;

		if (controlReliableConnect(getMissingRate()))
			resendWhenAsk = false;
        iop_usleep(minScanInterval);			// ʱ����
    }
}

void CReliableConnection::saveProcess() {
    while (isRunning) {
        WaitForSingleObject(semSave, 3000);
		// TODO for test
		if (lastUserNum != peerHub->size()) {
			cout << fileNamePrefix << " current users: " << peerHub->size() << endl;
		}
		lastUserNum = peerHub->size();

        pair<TS_UINT64, CPackage*> file;
        if (!saveQueue.deQueue(file))
            continue;

        bool isFirst = false;
        if (createdBlock.count(file.first) == 0) {
            createdBlock.insert(file.first);
            isFirst = true;
        }

        file.second->save(fileNamePrefix + "_" + int2string(file.first) + ".zip", isFirst);
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
	if (pids.empty())
		return 0;
#ifdef _DEBUG_INFO_
    cout << "ask for resend size is: " << pids.size() << endl;
#endif

	int result = 0;				
	auto iter = pids.begin();			// �ܹ�����ȥ������

	RCONNECT* r = new RCONNECT();

	r->head.type = RESEND;
	r->head.UID = selfUid;				// �Լ���UID
	r->head.sequence = 0;
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
		break;							// ÿ���û�ֻ��50�����󣬶��˾Ͳ���
	}

	delete r;
	return result;
}

void CReliableConnection::requestForSeriesResend(ts_msg& requestMsg) {
    DOWN_MAXSEQ_LIST *down = (DOWN_MAXSEQ_LIST*) &requestMsg;

    ts_msg msg;
    RCONNECT* up = (RCONNECT*) &msg;
    TS_UINT64 currentTotal = 0;

    if (requestCount > 0 && totalMsgs > 0) {    // has sent request and has recv anything
        --requestCount;
        return;
    } else {
        requestCount = 4;               // 4 * scan interval
    }

    for (int i = 0; i < down->count; i++) {
        TS_UINT64 uid = down->unit[i].uid;
        TS_UINT64 maxSeqClient = bm->getMaxSeqOfUID(uid);
        TS_UINT64 maxSeqServer = down->unit[i].maxSeq;
        if (0 == maxSeqClient)
            maxSeqClient = 1;           // 1 is begin

        assert(maxSeqClient >= 0 && maxSeqServer >= 0);

        cout << uid << " client/server max seq: " << maxSeqClient << " " << maxSeqServer << endl;
        if (maxSeqClient < maxSeqServer) {      // if server's seq bigger than client
            up->missingUID = uid;
            up->missingType = MISS_SERIES;
            up->count = 1;
            up->seq[0] = maxSeqClient;
            up->seq[1] = maxSeqServer;
            up->head.type = RESEND;
            up->head.size = sizeof(RCONNECT);
            up->head.sequence = 0;
            up->head.UID = selfUid;
            send(msg.Body, up->head.size);
            currentTotal += maxSeqServer - maxSeqClient;
        } else if (uid == selfUid) {            // if server lost client's latest msg
            if (maxSeqClient > maxSeqServer) {
                // only resend 1 max message for not block the network
                resendPart(ServerUID, selfUid, maxSeqClient, maxSeqClient);
            }
        }
    }
    totalMsgsOfClass = currentTotal;
}

int CReliableConnection::resend(ts_msg& requestMsg) {
	int count = 0;
	RCONNECT* r = (RCONNECT*) &requestMsg;
	TS_UINT64 uid = r->head.UID;					// ���󷽵�UID
	TS_UINT64 missingUID = r->missingUID;			// ����������UID
	
	ts_msg *p = new ts_msg();
	if (ServerUID == uid) {
		missingUID = selfUid;						// ����Server��������Լ��ģ�����client������Server������uid��
	}

	if (r->missingType == MISS_SINGLE) {			// ����MISS�ش�
        CPeerConnection *peer = findPeer(uid);		// ���󷽵ĵ�ַ
		if (NULL != peer) {
			for (int i = 0; i < r->count; i++) {
				if (bm->readRecord(missingUID, r->seq[i], *p) < 0)	// �����������󣬷�������
					continue;
				if (peer->send(p->Body, packetSize(*p)) > 0)
					count++;
			}
		}
    } else if (r->missingType == MISS_SERIES) {		// ����MISS�ش�
#ifdef _DEBUG_INFO_
		cout << "miss series" << endl;
#endif
        for (int i = 0; i < r->count; i++) {        // ÿ����seqΪһ��
			cout << "resend series " << r->seq[i*2 + 1] - r->seq[i*2] << " msg" << endl;
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


// ���ھͼ��һ��seq���������ȫ�������������
bool CReliableConnection::validityCheck(ts_msg& msg) {
    int size = packetSize(msg);
	if (size < sizeof(TS_MESSAGE_HEAD) || size > MESSAGE_SIZE)
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
#ifdef _DEBUG_INFO_
		cout << "user: " << uid << " has " << end << " message" << endl;
#endif
		for (int j = 1; j <= end; j++) {
			if (bm->readRecord(uid, j, p) < 0)
				continue;
			if (peer->send(p.Body, packetSize(p)) > 0)
				count++;
		}
	}
	iop_unlock(&mutex_lock);
#ifdef _DEBUG_INFO_
	cout << "resend all " << count << "message" << endl;
#endif
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
    for (TS_UINT64 j = fromSeq; j <= toSeq; j++) {
        if (bm->readRecord(needUID, j, p) < 0) {
			cout << "read " << needUID << " " << j << " failed" << endl;
            continue;
		}
        if (peer->send(p.Body, packetSize(p)) > 0)
            count++;
		iop_usleep(1);
		//if (j % 30 == 0)						// ��֪��Ϊʲô��������� ����78��һ�� ��֪��Ϊʲô��
		//	iop_usleep(30);
    }
    return count;
}

// only available on server mode
void CReliableConnection::sendMaxSeqList() {
    if (selfUid != ServerUID) {
        return;
    }
    DOWN_MAXSEQ_LIST msg;
    ts_msg *m = (ts_msg*) &msg;
    msg.head.size = sizeof(DOWN_MAXSEQ_LIST);
    msg.head.type = MAXSEQLIST;
    msg.head.UID = ServerUID;
    msg.head.version = VersionNumber;
	msg.head.sequence = 0;
	msg.head.time = getServerTime();
    msg.count = 0;
	
	bool hasUpPackage = false;
	
	iop_lock(&mutex_lock);
    for (auto iter = allUsers.begin(); iter != allUsers.end(); iter++) {
        TS_UINT64 maxSeq = bm->getMaxSeqOfUID(*iter);
        if (maxSeq == 0)
            continue;

		hasUpPackage = true;
        msg.unit[msg.count].uid = *iter;
        msg.unit[msg.count].maxSeq = maxSeq;
        msg.count++;

        if (msg.count == MaxSeqsInOnePacket / 2) {
            send(m->Body, msg.head.size);
            msg.count = 0;
        }
    }
    if (msg.count != 0 || !hasUpPackage) {		// ���һ������û�У�ҲҪ��������һ��
        send(m->Body, msg.head.size);
    }
	iop_unlock(&mutex_lock);
}

int CReliableConnection::getLoadingProcess() {
    if (totalMsgsOfClass < 0)
        return 0;
    else if (totalMsgsOfClass == 0)
        return 1000;
    else
        return 1000 * totalMsgs / totalMsgsOfClass;
}

void CReliableConnection::loadFile(string classname) {
    bm->loadLastClassProgress(classname);
}
