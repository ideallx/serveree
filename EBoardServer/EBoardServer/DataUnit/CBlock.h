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

const int initialHP = 200;

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
	set<CPackage*> saveList;	// ��Ҫ�����CPackage
	
	CPackage* curPackage;		// ��һ�ζ�ȡ���߲���İ���������
	int curPackageNum;			// ��һ�ΰ��İ���

	bool isFirstMsg;			// ��һ���������кŵ�����ʼ��

	map<int, int> blockHp;		// packageNum -> HP��ÿ��scan��Ѫ������0�����١�
	iop_lock_t mapLock;

	TS_UINT64 _uid;				// block��Ӧ��uid
	string fileNamePrefix;		// ���ļ�ʱ��ǰ׺

	TS_UINT64 maxSeq;			// ����Ϊֹ�յ�������seq

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

	// ��ȡ��ĳ����ſ�ʼ����ĳ����Ž��������е�msg
	int getMsgs(set<ts_msg*>& out, TS_UINT64 beg, TS_UINT64 end);

	// ��ȡ��Ҫ�����CPackages
	int savePackage(set<CPackage*>& out);

	// �����ļ���ǰ׺ fprefix_uid.zip/packageNum
	void setFilePrefix(string fprefix) { fileNamePrefix = fprefix; }

private:
	// ��ȡseq��Ӧ��msg���ڵ������Լ�λ��
	void getArrayNumberAndPos(TS_UINT64 seq, DWORD& packageNum, DWORD& pos);

	// ��ȡ�ض������ض�λ�õİ������
	TS_UINT64 getSequence(int packageNum, int pos);

};

#endif /* BLOCK_H_ */
