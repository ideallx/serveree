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

	set<int> missing;	// �Ѷ�ʧ�İ�

public:
	explicit CPackage(int beginPos = 0);
	virtual ~CPackage();
	void init();
	void unInit();	

	void clearPackets();
	
	int insert(const ts_msg& pin, int pos);
	int query(ts_msg& pout, int pos);
	
	// ������������е�msgд���ļ�
	bool save(string fileName, int packetNum, bool isCreate);
	// ���ļ��е�����ȫ�����Ƶ�����
	bool load(string fileName, int packetNum);

	// ���ĳzip�ļ��Ƿ���ڣ������new
	static bool testZipFileExist(string fileName, int packetNum);

	bool isExist(int pos);
	inline bool isAvailable(int pos) { return (pos < MaxPackets) && (pos >= 0); }
	inline bool isFull() { 
		if (scanHead == MaxPackets) 
			return missing.size() == 0;
		else
			return false;
	}

	// �����������ΪӦ���յ�����message
	void scanAll();

	int scanMissingPackets(set<int>& out);

	friend void* saveProc(LPVOID lpParam);
};

#endif