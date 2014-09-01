#ifndef _DATAUNIT_BLOCK_H_
#define _DATAUNIT_BLOCK_H_

#include <vector>
#include <set>
#include <map>
#include <assert.h>
#include <direct.h>
#include <semaphore.h>

#include "CMessage.h"
#include "CPackage.h"

using namespace std;

const int initialHP = 20;

class CBlock {
private:
	map<int, CPackage*> blockContents;
	
	CPackage* curPackage;		// ��һ�ζ�ȡ���߲���İ�
	int curPackageNum;			// ��һ�ΰ��İ���

	bool isFirstMsg;			// ��һ���������кŵ�����ʼ��

	map<int, int> blockHp;		// packageNum -> HP��ÿ��scan��Ѫ������0�����١�
	iop_lock_t mapLock;

	set<CPackage*> saveList;	// ��Ҫ�����CPackage

public:
	CBlock();
	virtual ~CBlock();

	void clear();

	// �����յ��İ������
	int addMsg(const ts_msg& _msg);

	// ��ȡseq��Ӧ��msg
	int readMsg(TS_UINT64 seq, ts_msg& pout);		

	// ��ȡ����array���Ե�ȱʧpid
	set<TS_UINT64> scanMissingPackets();

	// ȫ��������ļ�
	void saveAll();

	// ��ȡ��ĳ����ſ�ʼ����ĳ����Ž��������е�msg
	bool getMsgs(set<ts_msg*>& out, TS_UINT64 beg, TS_UINT64 end);

	// ��ȡ��Ҫ�����CPackages
	int savePackage(set<CPackage*>& out);
	
private:
	// ��ȡseq��Ӧ��msg���ڵ������Լ�λ��
	void getArrayNumberAndPos(TS_UINT64 seq, DWORD& packageNum, DWORD& pos);
	// ��ȡ�ض������ض�λ�õİ������
	TS_UINT64 getSequence(int packageNum, int pos);

	// ���棬д�ļ�����
	void cachePrivacy(int packageNum, CPackage& p);

};

#endif /* BLOCK_H_ */
