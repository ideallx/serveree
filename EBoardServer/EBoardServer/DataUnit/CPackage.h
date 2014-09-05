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

/*
 *	ÿ1024��msgs��Ϊһ������
 *
 *	scanHead: �յ�������pos + 1
 *	missing: ��ʧ�İ�
 *
 *	insert����:
 *		1:	��Ч���ж�
 *		2:	����������pos��scanHead����pos��Ϊ�µ�scanHead
 *		3:	pos��scanHead֮���ȫ�����뵽missing����
 *		4:	����������pos��scanHeadС�����ж��Ƿ����missing�У����ǣ���ɾ��
 *
 *	scanAll:
 *		��Ϊ��������е�msg��Ӧ�ñ��յ���
 */


class CPackage {
private:
	ts_msg* packets[MaxPackets];
	
	int scanHead;		// �´�ɨ��Ŀ�ͷ��
	int packageID;		// ��id
	set<int> missing;	// �Ѷ�ʧ�İ�
	bool _isSaved;		// �Ƿ��Ѿ������

public:
	explicit CPackage(int beginPos = 0);
	virtual ~CPackage();
	void init();
	void unInit();	

	void clearPackets();
	
	int insert(const ts_msg& pin, int pos);
	int query(ts_msg& pout, int pos);
	
	// ������������е�msgд���ļ�
	bool save(string fileName, bool isCreate);
	// ���ļ��е�����ȫ�����Ƶ�����
	bool load(string fileName, int packageNum);

	// ���ظ�package�Ƿ��Ѿ�����ļ�
	inline bool isSaved() { return _isSaved; }
	// ���ø�package�Ƿ��Ѿ�����ļ�
	inline void setSaved(bool set) { _isSaved = set; }

	// ���ĳzip�ļ��Ƿ���ڣ������new
	static bool isZipFileExist(string fileName, int packageNum);

	bool isExist(int pos);
	inline bool isAvailable(int pos) { return (pos < MaxPackets) && (pos >= 0); }
	inline bool isFull() { 
		if (scanHead == MaxPackets) 
			return missing.size() == 0;
		else
			return false;
	}

	inline void setID(int id) { packageID = id; }
	inline int getID(void) { return packageID; }

	// �����������ΪӦ���յ�����message
	void scanAll();

	int scanMissingPackets(set<int>& out);

	friend void* saveProc(LPVOID lpParam);
};

#endif