#ifndef _DATAUNIT_CPACKETARRAY_H_
#define _DATAUNIT_CPACKETARRAY_H_

#include <set>
#include <iop_thread.h>

#include "CMessage.h"
#include "../../Stdafx.h"
#include "../Zip/zip.h"
#include "../Zip/unzip.h"
#include "../Zip/zlib.h"

using namespace std;

const int RemaningID = 2000;


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
 *	needAll:
 *		��Ϊ��������е�msg��Ӧ�ñ��յ���
 */


class CPackage {
private:
	ts_msg* packets[MaxPackets];
	
	int scanHead;		// �´�ɨ��Ŀ�ͷ��
	int packageID;		// ��id
	set<int> missing;	// �Ѷ�ʧ�İ�
	bool _isSaved;		// �Ƿ��Ѿ������
    TS_UINT64 m_lastKey;  // ���keyֵ

public:
	explicit CPackage(int beginPos = 0);
    virtual ~CPackage();

	inline int lastSubSeq() { return scanHead; }
	void clearPackets();
	
	int insert(const ts_msg& pin, int pos);
	int query(ts_msg& pout, int pos);
	
	// ������������е�msgд���ļ�
	bool save(string fileName, bool isCreate);

    bool forceSave(string fileName, bool isCreate);
	// ���ļ��е�����ȫ�����Ƶ�����
	bool load(string fileName, int packageNum);

	// ���ظ�package�Ƿ��Ѿ�����ļ�
	inline bool isSaved() { return _isSaved; }
	// ���ø�package�Ƿ��Ѿ�����ļ�
	inline void setSaved(bool set) { _isSaved = set; }

	// ���ĳzip�ļ��Ƿ���ڣ������new
	static bool isZipFileExist(string fileName, int packageNum);

	bool isExist(int pos);
	inline bool isAvailable(int pos) { return ((pos < MaxPackets) && (pos >= 0)); }
	inline bool isFull() { 
		if (scanHead >= MaxPackets) 
			return missing.empty();
		else
			return false;
	}

	inline void setID(int id) { packageID = id; }
	inline int getID(void) { return packageID; }

	// �����������ΪӦ���յ�����message
	void needAll();

	int scanMissingPackets(set<int>& out);

    const ts_msg* operator[] (const size_t index) {
        if (!isAvailable(index))
            return NULL;
        return packets[index];
    }
};

#endif
