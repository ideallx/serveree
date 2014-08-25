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

const int initialHP = 10;

class CBlock {
private:
	map<int, CPackage*> blockContents;
	bool isFirstWrite;			// 是否是第一次写文件

	string zipName;				// 保存的zip文件名
	
	CPackage* curPackage;		// 上一次读取或者插入的包
	int curPackageNum;			// 上一次包的包号

	bool isFirstMsg;			// 第一个包的序列号当做起始号

	map<int, int> blockHp;		// packetNum -> HP

	iop_lock_t mapLock;

public:
	CBlock();
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

	// 创建zip文件
	// 文件路径的格式： runtime path/_classid_time_uid.zip/arrayNumber，同一数组中的packet写在一个文件中
	void setZipName(string zip) { zipName = zip; }
	
private:
	// 获取seq对应的msg所在的数组以及位置
	void getArrayNumberAndPos(TS_UINT64 seq, DWORD& packageNum, DWORD& pos);
	// 获取特定数组特定位置的包的序号
	TS_UINT64 getSequence(int packageNum, int pos);

	// 缓存，写文件策略
	void cachePrivacy(int packageNum, CPackage& p);

};

#endif /* BLOCK_H_ */
