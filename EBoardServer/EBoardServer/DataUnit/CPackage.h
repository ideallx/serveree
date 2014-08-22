#ifndef _DATAUNIT_CPACKETARRAY_H_
#define _DATAUNIT_CPACKETARRAY_H_

#include <set>

#include <iop_thread.h>
#include <semaphore.h>

#include "../Stdafx.h"
#include "CMessage.h"

#include "../Zip/zip.h"
#include "../Zip/unzip.h"
#include "../Zip/zlib.h"

using namespace std;

const int MaxPackets = 1024;

class CPackage {
private:
	ts_msg* packets[MaxPackets];
	
	int scanHead;

	HANDLE semPackage;

	set<int> missing;	// 已丢失的包

public:
	explicit CPackage(int beginPos = 0);
	virtual ~CPackage();
	void init();
	void unInit();	

	void clearPackets();
	
	int insert(const ts_msg& pin, int pos);
	int query(ts_msg& pout, int pos);
	
	// 将这个类中所有的msg写进文件
	bool save(string fileName, int packetNum, bool isCreate);
	// 将文件中的内容全部复制到类中
	bool load(string fileName, int packetNum);

	// 检测某zip文件是否存在，以免多new
	static bool testZipFileExist(string fileName, int packetNum);

	bool isExist(int pos);
	inline bool isAvailable(int pos) { return (pos < MaxPackets) && (pos >= 0); }
	inline bool isFull() { 
		if (scanHead == MaxPackets) 
			return missing.size() == 0;
		else
			return false;
	}

	// 将这个包设置为应该收到所有message
	void scanAll();

	int scanMissingPackets(set<int>& out);

	friend void* saveProc(LPVOID lpParam);
};

#endif