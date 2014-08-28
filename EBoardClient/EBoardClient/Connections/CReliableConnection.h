#ifndef _CONNECTION_CRELIABLECONNECTION_H_
#define _CONNECTION_CRELIABLECONNECTION_H_

#include <pthread.h>
#include <iop_thread.h>

#include "CHubConnection.h"
#include "../DataUnit/CBlockManager.h"
#include "../DataStructure/TSQueue.h"


class CReliableConnection : public CHubConnection {
protected:
	pthread_t msgScan;	
	pthread_t msgIn;
	
	// ���ն���
	// sem_t semMsg;
	HANDLE semMsg;

	CBlockManager* bm;
	bool needCacheSend;		// �Ƿ���Ҫ��send�����ݻ�������
	TSQueue<ts_msg>* msgQueue;
	
	TS_UINT64 selfUid;

public:

	CReliableConnection();
	virtual ~CReliableConnection();

	// ����socket��������scan�߳�
	bool create(unsigned short localport = 0);

	// ��ͣ�հ����쳣���Լ����������������ϲ㣬������Ϣ����
	int recv(char* buf, ULONG& len);

	// ����ʱ���渱��
	int send(const char* buf, ULONG len);

	// ɨ��һ������block�����ж�ʧ�ľͷ����ط�����
	void scanProcess();

	// ��ȡBlockManager���ļ���ַ
	string getFilePath();

	// ��ĳ���û��İ�ȫ��������ļ��У���ɾ��֮
	void saveUserBlock(TS_UINT64 uid);

	// �򿪻��߹ر�sendʱ�������
	inline void switchSendCache(bool on = true) { needCacheSend = on; }
	
	// ��UID������Server����Client�ˣ������ش�����ʱ��Ҫ�ṩ�Լ���UID
	void setUID(TS_UINT64 in) { selfUid = in; }

private:
	// ����Ҫ���͵���Ϣ�������Ϣ����
	int send2Peer(ts_msg& msg);

	// ����Ҫ���͵���Ϣ�������Ϣ���У����͸���һ��uid��Ӧ�ĵ�ַ
	int send2Peer(ts_msg& msg, TS_UINT64 uid);

	// �Լ�����ȱʧ���ʶԶ�Ҫ�����ط���ȥ�˼�����  ��ͷ�ĺ�����
	int requestForResend(TS_UINT64 uid, set<TS_UINT64> pids);

	// �Լ�����ȱʧ������Զ����󣬷��ط���ȥ�˼�����
	int resend(ts_msg& requestMsg);

	// ���ݱ�����Ч�Լ��
	bool validityCheck(ts_msg& msg);
	
private:
	// ��ʱɨ��ʧ�ٰ�����
	friend void* ScanProc(LPVOID lpParam);

	// ��Ϣ����Ĵ������
	friend void* MsgInProc(LPVOID lpParam);

	friend int testRecv();

	set<TS_UINT64> missed;
};


#endif