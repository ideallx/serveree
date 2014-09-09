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
 *	最重要的数据单元，保存单个用户的所有数据
 *
 *  包含:
 *		1:	所有留在内存中的CPackage表，blockContents
 *		2:	每个CPackage对应的HP，每次scan扣一次，扣完存文件（加入到saveList中，由上层来存）
 *	
 *
 *	加入msg过程：
 *		1:	若是最大序号，则保存序号
 *		2:	获取对应的packageNum和pos
 *		3:	若是对应的package不存在，则创建一个，并添加该CPackage的HP
 *		4:	将数据插入对应位置
 *
 *	读取msg过程：
 *		1:	获取对应的packageNum和pos
 *		2:	若是对应的package不存在，则读文件读出来，并将整个package读出来加进内存，添加CPackage的HP
 *		3:  读出对应数据
 *
 *	扫描丢包过程：
 *		1:	获取每个内存中的Package的丢失的Msgs
 *		2:	扫描已满的Cpackage并加入saveList中
 *		3:	每个package扣血，扣完的销毁
 */

class CBlock {
private:
	map<int, CPackage*> blockContents;
	set<CPackage*> saveList;	// 需要保存的CPackage
	
	CPackage* curPackage;		// 上一次读取或者插入的包，缓存用
	int curPackageNum;			// 上一次包的包号

	bool isFirstMsg;			// 第一个包的序列号当做起始号

	map<int, int> blockHp;		// packageNum -> HP，每次scan减血，减到0了销毁。
	iop_lock_t mapLock;

	TS_UINT64 _uid;				// block对应的uid
	string fileNamePrefix;		// 存文件时的前缀

	TS_UINT64 maxSeq;			// 至今为止收到的最大的seq

public:
	CBlock(TS_UINT64 uid);
	virtual ~CBlock();

	void clear();

	// 把新收到的包存进来
	int addMsg(const ts_msg& _msg);

	// 读取seq对应的msg
	int readMsg(TS_UINT64 seq, ts_msg& pout);		

	// 获取各个array各自的缺失pid
	set<TS_UINT64> scanMissingPackets();

	// 全部保存进文件
	void saveAll();

	// 获取从某个序号开始，到某个序号结束的所有的msg
	int getMsgs(set<ts_msg*>& out, TS_UINT64 beg, TS_UINT64 end);

	// 获取需要保存的CPackages
	int savePackage(set<CPackage*>& out);

	// 设置文件名前缀 fprefix_uid.zip/packageNum
	void setFilePrefix(string fprefix) { fileNamePrefix = fprefix; }

	inline TS_UINT64 getMaxSeq() { return maxSeq; }

private:
	// 获取seq对应的msg所在的数组以及位置
	void getArrayNumberAndPos(TS_UINT64 seq, DWORD& packageNum, DWORD& pos);

	// 获取特定数组特定位置的包的序号
	TS_UINT64 getSequence(int packageNum, int pos);

};

#endif /* BLOCK_H_ */
