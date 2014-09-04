#ifndef _DATAUNIT_BLOCKMANAGER_H_
#define _DATAUNIT_BLOCKMANAGER_H_

#include <map>
#include <set>

#include "CBlock.h"
#include "../Stdafx.h"

class CBlockManager {
private:
	map<TS_UINT64, CBlock*> map_userBlock;		// 所有用户对应的Block
	string fileNamePrefix;						// 保存的文件名的前缀

public:
	CBlockManager();
	virtual ~CBlockManager();

	// 找某个用户的某条记录
	int readRecord(TS_UINT64 uid, TS_UINT64 seq, ts_msg& p);

	// 记录一条记录
	int record(ts_msg& in);

	// 获取每个User所有丢失的包的序号
	map<TS_UINT64, set<TS_UINT64> > getLostSeqIDs();

	// 移除Block
	void removeBlock(TS_UINT64 uid);

	// 保存Block
	void saveBlock(TS_UINT64 uid);

	// 获取需要保存的CPackage
	int getSavePackage(set<pair<TS_UINT64, CPackage*> >& out);

	// 设置文件名前缀 fprefix_uid.zip/packageNum
	void setFilePrefix(string fprefix) { fileNamePrefix = fprefix; }

	// 获取每个用户所有的包
	int getAllMsgs(set<ts_msg*>& out);

private:
	CBlock* getBlockByUid(TS_UINT64 uid);

};

#endif