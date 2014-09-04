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

class CBlock {
private:
	map<int, CPackage*> blockContents;
	set<CPackage*> saveList;	// 需要保存的CPackage
	
	CPackage* curPackage;		// 上一次读取或者插入的包
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

private:
	// 获取seq对应的msg所在的数组以及位置
	void getArrayNumberAndPos(TS_UINT64 seq, DWORD& packageNum, DWORD& pos);

	// 获取特定数组特定位置的包的序号
	TS_UINT64 getSequence(int packageNum, int pos);

};

#endif /* BLOCK_H_ */
