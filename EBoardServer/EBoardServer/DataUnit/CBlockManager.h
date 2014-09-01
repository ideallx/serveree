#ifndef _DATAUNIT_BLOCKMANAGER_H_
#define _DATAUNIT_BLOCKMANAGER_H_

#include <map>
#include <set>

#include "CBlock.h"
#include "../Stdafx.h"

class CBlockManager {
public:
	CBlockManager();
	virtual ~CBlockManager();

	// ��ĳ���û���ĳ����¼
	int readRecord(TS_UINT64 uid, TS_UINT64 seq, ts_msg& p);

	// ��¼һ����¼
	int record(ts_msg& in, int size);

	// ��ȡÿ��User���ж�ʧ�İ������
	map<TS_UINT64, set<TS_UINT64> > getLostSeqIDs();

	// �Ƴ�Block
	void removeBlock(TS_UINT64 uid);

	// ����Block
	void saveBlock(TS_UINT64 uid);

	// ��ȡ��Ҫ�����CPackage
	int getSavePackage(set<pair<TS_UINT64, CPackage*> >& out);

private:
	CBlock* getBlockByUid(TS_UINT64 uid);

private:
	map<TS_UINT64, CBlock*> map_userBlock;

	TS_UINT64 classid;
};

#endif