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
	pthread_t msgSave;
	
	// ���ն���
	HANDLE semMsg;					// ��Ϣ�����ź���
	HANDLE semSave;					// ���ļ��ź���

	CBlockManager* bm;

	TSQueue<ts_msg>* msgQueue;
	TSQueue<pair<TS_UINT64, CPackage*> > saveQueue;	// bao���ﴫָ��Ӧ��û����ɡ�

	TS_UINT64 selfUid;				// �����UID
	set<TS_UINT64> missed;			// ������client��������

	set<TS_UINT64> createdBlock;	// ��¼����create����block

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

	// ���ļ��̣߳�ά��һ�����ļ�����
	void saveProcess();

	// ��ȡBlockManager���ļ���ַ
	string getFilePath();

	// ��ĳ���û��İ�ȫ��������ļ��У���ɾ��֮
	void saveUserBlock(TS_UINT64 uid);

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

	// ��Ϣ����Ĵ������
	friend void* SaveProc(LPVOID lpParam);

	friend int testRecv();
};


#endif