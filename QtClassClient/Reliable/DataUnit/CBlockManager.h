#ifndef _DATAUNIT_BLOCKMANAGER_H_
#define _DATAUNIT_BLOCKMANAGER_H_

#include <map>
#include <set>

#include "CBlock.h"
#include "CMessage.h"

/*
 * 保存文件管理单元，所有用户都由他控制，包含：
 *		1:	Block表map_userBlock，每个Block对应一个用户 
 *
 * 数据单元结构:
 *		1:	Msg，一条报文
 *		2:	Package，以1024条Msg（UID必须一致）组成的数组为单位，保存数据
 *		3:	Block，掌管一个Package表，为单个UID所有的数据
 *		4:	BlockManager，掌管Block表，包含了所有的数据
 *	
 *	读/写
 *		根据UID，选择对应的Block进行操作
 */

class CBlockManager {
private:
	map<TS_UINT64, CBlock*> map_userBlock;		// 所有用户对应的Block
	string fileNamePrefix;						// 保存的文件名的前缀
	iop_lock_t	lockUserBlock;

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

    // 设置某个UID当前应该收到的最大的SEQ
    void setMaxSeqOfUid(TS_UINT64 uid, TS_UINT64 seq);

	// 获取某个UID当前收到的最大的SEQ
	TS_UINT64 getMaxSeqOfUID(TS_UINT64 uid);

private:
	CBlock* getBlockByUid(TS_UINT64 uid);

};

#endif
