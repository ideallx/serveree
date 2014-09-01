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

	// 找某个用户的某条记录
	int readRecord(TS_UINT64 uid, TS_UINT64 seq, ts_msg& p);

	// 记录一条记录
	int record(ts_msg& in, int size);

	// 获取每个User所有丢失的包的序号
	map<TS_UINT64, set<TS_UINT64> > getLostSeqIDs();

	// 移除Block
	void removeBlock(TS_UINT64 uid);

	// 保存Block
	void saveBlock(TS_UINT64 uid);

	// 获取需要保存的CPackage
	int getSavePackage(set<pair<TS_UINT64, CPackage*> >& out);

private:
	CBlock* getBlockByUid(TS_UINT64 uid);

private:
	map<TS_UINT64, CBlock*> map_userBlock;

	TS_UINT64 classid;
};

#endif