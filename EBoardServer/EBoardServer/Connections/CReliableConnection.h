#ifndef _CONNECTION_CRELIABLECONNECTION_H_
#define _CONNECTION_CRELIABLECONNECTION_H_

#include <pthread.h>
#include <iop_thread.h>

#include "CHubConnection.h"
#include "../DataUnit/CBlockManager.h"
#include "../DataStructure/TSQueue.h"


/**
 *  �ɿ�UDP���ں���
 *		1:	BlockManager �������з������յ��ļ�
 *		2:	�����߳�
 *			2.1:scan�̣߳�ɨ�趪����ɨ����Ҫ����İ�
 *			2.2:save�̣߳�scanʱɨ����Ҫ����İ����򽻸�save�̵߳Ķ��У���save�߳̽��д��ļ�����
 *			2.3:msgin�̣߳����յ���Ϣ��ͽ���msgIn�̣߳�����msgIn������msg������ѡ����б�������ط�����
 *		3:	�������У���ʹ���ź������б���
 *			3.1:msgQueue���յ���msg
 *			3.2:saveQueue����Ҫ�����package����
 *
 *	��msg���̣�
 *		�յ�msg������msgQueue����������msg�򷵻��ϲ�msg���ȣ�
 *							  �����쳣�򷵻�-1
 *		msgin�̶߳�ȡ��msg����������msg�򱣴浽blockmanager
 *						   �����쳣������ط�����
 *
 *  ���͹��̣�
 *		���͸����˵ģ�ʹ��send()�������Ⱥ��
 *		���͸�����ʹ��send2peer()������ݱ��ĵ�UID��ѡ��peer����
 *		Ҫ���˷��Ͷ������ʹ��findpeer()->send
 *		�ͻ��˷���ʱ���ᱣ�渱����
 *
 *	ɨ����̣�
 *		�򿪶˿ں󣬿���scan�߳�
 *		ÿ���ض�ʱ�䣨������100ms)����һ���жϣ��ж�2��
 *			����ȱ��ĳ���������������ط�
 *			���ǻ�ȡ����ĳ������Ҫ����İ��������saveQueue���ȴ������߳̽��б���
 *
 *	������̣�
 *		�򿪶˿ں󣬿���save�߳�
 *		ʹ���ź���������saveQueue�������package���룬����б���
 *
 *
 *	����:
 *		1.������: ÿmissһ�� totalMiss++�� ÿ�յ�һ�� totalMsgs++
 *				 ������ = totalMiss / totalMsgs * 100�����ڿ����ظ�miss�����Զ����ʿ��ܹ�100
 *		2.createdBlock: ����ÿ��block�ĵ�һ�δ����ļ���Ҫ��createģʽ�����������¼�Ƿ��ǵ�һ�δ��ļ�
 *		3.selfUid: ����UID��ͬʱ�����ж��Ƿ���server
 *		4.fileNamePrefix:���α�����ļ���ǰ׺��һ��Ϊclassid_time
 */

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
	TSQueue<pair<TS_UINT64, CPackage*> > saveQueue;	// ���ﴫָ��Ӧ��û����ɡ�

	TS_UINT64 selfUid;				// �����UID
	set<TS_UINT64> missed;			// ������client��������

	set<TS_UINT64> createdBlock;	// ��¼����create����block

	int totalMsgs;					// �ܹ��յ��İ���
	int totalMiss;					// �ܹ������İ���

	string fileNamePrefix;			// ������ļ�����ǰ׺

	HANDLE needScan;				// �����µ�msg����Ҫ����scan

	bool resendWhenAsk;				// �Ƿ�һ�յ��ط�������ط����ط��ʹ���ʱ����Ϊfalse�����ط���

public:
	bool isRunning;					// �Ƿ����У���create��ʼ����

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

	// �����ļ���ǰ׺ fprefix_uid.zip/packageNum
	void setFilePrefix(string fprefix);

	// ��ȡ�����ʣ�ǧ�ֱ� ����1000������Ƿ���������
	inline int getMissingRate() { return 1000 * totalMiss / totalMsgs; }

	// ���а�ȫ���ط�һ��
	int resendAll(TS_UINT64 toUID);

	// �ط�ĳ���û��Ĳ��ְ�
	int resendPart(TS_UINT64 toUID, TS_UINT64 needUID, 
					TS_UINT64 fromSeq, TS_UINT64 toSeq);

	// �����������������ط�
	inline void setResendWhenAsk(bool set) { resendWhenAsk = set; }

	// �ر�reliable
	inline void stop() { isRunning = false; }

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

	// �յ����ݺ�Ĵ����Լ�ת���ȹ���
	void receive(ts_msg& msg);
	
private:
	// ��ʱɨ��ʧ�ٰ�����
	friend void* ScanProc(LPVOID lpParam);

	// ��Ϣ����Ĵ������
	friend void* MsgInProc(LPVOID lpParam);

	// ��Ϣ����Ĵ������
	friend void* SaveProc(LPVOID lpParam);
};


#endif