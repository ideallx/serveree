#ifndef _DATAUNIT_BLOCKMANAGER_H_
#define _DATAUNIT_BLOCKMANAGER_H_

#include <map>
#include <set>

#include "CBlock.h"
#include "CMessage.h"

/*
 * �����ļ�����Ԫ�������û����������ƣ�������
 *		1:	Block��map_userBlock��ÿ��Block��Ӧһ���û� 
 *
 * ���ݵ�Ԫ�ṹ:
 *		1:	Msg��һ������
 *		2:	Package����1024��Msg��UID����һ�£���ɵ�����Ϊ��λ����������
 *		3:	Block���ƹ�һ��Package��Ϊ����UID���е�����
 *		4:	BlockManager���ƹ�Block�����������е�����
 *	
 *	��/д
 *		����UID��ѡ���Ӧ��Block���в���
 */

class CBlockManager {
private:
	map<TS_UINT64, CBlock*> map_userBlock;		// �����û���Ӧ��Block
	string fileNamePrefix;						// ������ļ�����ǰ׺
	iop_lock_t	lockUserBlock;

public:
	CBlockManager();
	virtual ~CBlockManager();

	// ��ĳ���û���ĳ����¼
	int readRecord(TS_UINT64 uid, TS_UINT64 seq, ts_msg& p);

	// ��¼һ����¼
	int record(ts_msg& in);

	// ��ȡÿ��User���ж�ʧ�İ������
	map<TS_UINT64, set<TS_UINT64> > getLostSeqIDs();

	// �Ƴ�Block
	void removeBlock(TS_UINT64 uid);

	// ����Block
	void saveBlock(TS_UINT64 uid);

	// ��ȡ��Ҫ�����CPackage
	int getSavePackage(set<pair<TS_UINT64, CPackage*> >& out);

	// �����ļ���ǰ׺ fprefix_uid.zip/packageNum
	void setFilePrefix(string fprefix) { fileNamePrefix = fprefix; }

    // ����ĳ��UID��ǰӦ���յ�������SEQ
    void setMaxSeqOfUid(TS_UINT64 uid, TS_UINT64 seq);

	// ��ȡĳ��UID��ǰ�յ�������SEQ
	TS_UINT64 getMaxSeqOfUID(TS_UINT64 uid);

private:
	CBlock* getBlockByUid(TS_UINT64 uid);

};

#endif
