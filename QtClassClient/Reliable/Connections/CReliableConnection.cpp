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
        iop_usleep(200);
        iop_thread_cancel(pthread_input);
        iop_thread_cancel(pthread_scan);
        iop_thread_cancel(pthread_save);
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
		cout << "MsgIn Thread start failed " << endl;
		isRunning = false;
		return false;
	}

    rc = iop_thread_create(&pthread_save, MsgInProc, (void *) this, 0);
	if (0 == rc) {
		iop_usleep(10);
#ifdef _DEBUG_INFO_
		cout << "MsgSave Thread start successfully" << endl;
#endif
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
    case MAXSEQLIST:
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

int CReliableConnection::send(const char* buf, ULONG len, TS_UINT64 uid) {
	ts_msg *msg = (ts_msg*) buf;
	TS_UINT64 seq = getSeq(*msg);

    // hub::send is same to send2peer uid in client mode for peerhub of hub is only server inside
	if (seq != 0) {												// seqΪ0��������ָ��ݲ�����
        if (selfUid != ServerUID) {								// client�����⴦��.
			bm->record(*msg);									// client����Ҫ��¼�����İ�
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
        WaitForSingleObject(needScan, 1000);	// ����1��
        // ɨ�趪�����ط�
        totalMiss = 0;
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

        // send User maxSeq list to all client every 10 scanprocess in server
        if (selfUid == ServerUID) {
            static int scanTimes = 0;
            scanTimes++;
            sendMaxSeqList();
        }
#ifdef _DEBUG_INFO_
        cout << "missing: " << totalMiss;
#endif
        iop_usleep(100);			// ʱ����
    }
}

void CReliableConnection::saveProcess() {
    while (isRunning) {
        WaitForSingleObject(semSave, 3000);

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
        // cout << "Missing Rate: " << getMissingRate() << endl;
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
	// cout << "port:" << peer->getPeer()->sin_port << endl;
	return peer->send(msg.Body, packetSize(msg));
}

int CReliableConnection::requestForResend(TS_UINT64 uid, set<TS_UINT64> pids) {
	if (pids.size() == 0)
		return 0;
#ifdef _DEBUG_INFO_
    cout << "ask for resend size is: " << pids.size() << endl;
#endif

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

void CReliableConnection::requestForSeriesResend(ts_msg& requestMsg) {
    DOWN_MAXSEQ_LIST *down = (DOWN_MAXSEQ_LIST*) &requestMsg;

    ts_msg msg;
    RCONNECT* up = (RCONNECT*) &msg;
    for (int i = 0; i < down->count; i++) {
        TS_UINT64 uid = down->seq[2 * i];
        TS_UINT64 maxSeqClient = bm->getMaxSeqOfUID(uid);
        TS_UINT64 maxSeqServer = down->seq[2 * i + 1];
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
        } else if (uid == selfUid) {            // if server lost client's latest msg
            if (maxSeqClient > maxSeqServer) {
                resendPart(ServerUID, selfUid, maxSeqServer, maxSeqClient);
            }
        }
    }
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
        if (NULL == peer)
            return -1;

		for (int i = 0; i < r->count; i++) {
			if (bm->readRecord(missingUID, r->seq[i], *p) < 0)	// �����������󣬷�������
                continue;
			if (peer->send(p->Body, packetSize(*p)) > 0)
				count++;
		}
    } else if (r->missingType == MISS_SERIES) {		// ����MISS�ش�
#ifdef _DEBUG_INFO_
		cout << "miss series" << endl;
#endif
        for (int i = 0; i < r->count; i++) {        // ÿ����seqΪһ��
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

void CReliableConnection::receive() {
    ts_msg msg;
    while (isRunning) {
        WaitForSingleObject(semMsg, 3000);

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
        default:                                // �����յ��ش������Լ�����
            bm->record(msg);					// �����¼
            if (selfUid == ServerUID) {			// Serverת��
                send(msg.Body, packetSize(msg));
            }
            break;
        }
        ReleaseSemaphore(needScan, 1, NULL);	// �յ�����msg����Ҫ����scan
    }
}

// ���ھͼ��һ��seq���������ȫ�������������
bool CReliableConnection::validityCheck(ts_msg& msg) {
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
        if (bm->readRecord(needUID, j, p) < 0)
            continue;
        if (peer->send(p.Body, packetSize(p)) > 0)
            count++;
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
    msg.count = 0;

    for (auto iter = allUsers.begin(); iter != allUsers.end(); iter++) {
        TS_UINT64 maxSeq = bm->getMaxSeqOfUID(*iter);
        if (maxSeq != 0) {  // the user whose seq is nonzero can be listed
            msg.seq[msg.count * 2] = *iter;
            msg.seq[msg.count * 2 + 1] = maxSeq;
            msg.count++;
        }

        if (msg.count == MaxSeqsInOnePacket / 2) {
            send(m->Body, msg.head.size);
            msg.head.size = 0;
        }
    }
    if (msg.head.size != 0) {
        send(m->Body, msg.head.size);
    }
}

thread_ret_type thread_func_call ScanProc(LPVOID lpParam) {
    iop_thread_detach_self();
    CReliableConnection* conn = (CReliableConnection*) lpParam;
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
    CReliableConnection* conn = (CReliableConnection*) lpParam;
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
    CReliableConnection* conn = (CReliableConnection*) lpParam;
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
