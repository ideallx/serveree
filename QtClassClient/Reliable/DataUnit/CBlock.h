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

#include "../Strategy/CDestroyStrategy.h"
#include "../Strategy/CWriteFileStrategy.h"

using namespace std;


/**
 *	����Ҫ�����ݵ�Ԫ�����浥���û�����������
 *
 *  ����:
 *		1:	���������ڴ��е�CPackage��blockContents
 *		2:	ÿ��CPackage��Ӧ��HP��ÿ��scan��һ�Σ�������ļ������뵽saveList�У����ϲ����棩
 *	
 *
 *	����msg���̣�
 *		1:	���������ţ��򱣴����
 *		2:	��ȡ��Ӧ��packageNum��pos
 *		3:	���Ƕ�Ӧ��package�����ڣ��򴴽�һ��������Ӹ�CPackage��HP
 *		4:	�����ݲ����Ӧλ��
 *
 *	��ȡmsg���̣�
 *		1:	��ȡ��Ӧ��packageNum��pos
 *		2:	���Ƕ�Ӧ��package�����ڣ�����ļ�����������������package�������ӽ��ڴ棬���CPackage��HP
 *		3:  ������Ӧ����
 *
 *	ɨ�趪�����̣�
 *		1:	��ȡÿ���ڴ��е�Package�Ķ�ʧ��Msgs
 *		2:	ɨ��������Cpackage������saveList��
 *		3:	ÿ��package��Ѫ�����������
 */

class CBlock {
private:
	map<int, CPackage*> blockContents;
	
    CPackage* curPackage;		// ��һ�ζ�ȡ���߲���İ���������
	iop_lock_t mapLock;

	TS_UINT64 _uid;				// block��Ӧ��uid
	string fileNamePrefix;		// ���ļ�ʱ��ǰ׺

	TS_UINT64 maxSeq;			// ����Ϊֹ�յ�������seq

	CDestroyStrategy* straDestroy;	// ����CPackage����
	CWriteFileStrategy* straWrite;	// CPackage���ļ�����

public:
	CBlock(TS_UINT64 uid);
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

	// ��ȡ��Ҫ�����CPackages
	inline int savePackage(set<CPackage*>& out) { return straWrite->getStrategyResult(out); }

	// �����ļ���ǰ׺ fprefix_uid.zip/packageNum
	void setFilePrefix(string fprefix) { fileNamePrefix = fprefix; }

	inline TS_UINT64 getMaxSeq() { return maxSeq; }

    void setMaxSeq(TS_UINT64 seq);

private:
	// ��ȡseq��Ӧ��msg���ڵ������Լ�λ��
	void getArrayNumberAndPos(TS_UINT64 seq, DWORD& packageNum, DWORD& pos);

	// ��ȡ�ض������ض�λ�õİ������
	TS_UINT64 getSequence(int packageNum, int pos);

	// ���ļ�����
	bool saveStrategy(CPackage* pack);

	// �������ڲ���
	bool lifeStrategy(CPackage* pack);

	void addToLifeStrategy(CPackage* pack);
};

#endif /* BLOCK_H_ */
