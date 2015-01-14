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
 *	每1024个msgs作为一个数组
 *
 *	scanHead: 收到的最大的pos + 1
 *	missing: 丢失的包
 *
 *	insert过程:
 *		1:	有效性判断
 *		2:	若是新来的pos比scanHead大，则pos作为新的scanHead
 *		3:	pos和scanHead之间的全部加入到missing表中
 *		4:	若是新来的pos比scanHead小，则判断是否存在missing中，若是，则删除
 *
 *	needAll:
 *		认为这个包所有的msg都应该被收到过
 */


class CPackage {
private:
	ts_msg* packets[MaxPackets];
	
	int scanHead;		// 下次扫描的开头点
	int packageID;		// 包id
	set<int> missing;	// 已丢失的包
	bool _isSaved;		// 是否已经保存过
    TS_UINT64 m_lastKey;  // 最大key值

public:
	explicit CPackage(int beginPos = 0);
    virtual ~CPackage();

	inline int lastSubSeq() { return scanHead; }
	void clearPackets();
	
	int insert(const ts_msg& pin, int pos);
	int query(ts_msg& pout, int pos);
	
	// 将这个类中所有的msg写进文件
	bool save(string fileName, bool isCreate);

    bool forceSave(string fileName, bool isCreate);
	// 将文件中的内容全部复制到类中
	bool load(string fileName, int packageNum);

	// 返回该package是否已经存过文件
	inline bool isSaved() { return _isSaved; }
	// 设置该package是否已经存过文件
	inline void setSaved(bool set) { _isSaved = set; }

	// 检测某zip文件是否存在，以免多new
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

	// 将这个包设置为应该收到所有message
	void needAll();

	int scanMissingPackets(set<int>& out);

    const ts_msg* operator[] (const size_t index) {
        if (!isAvailable(index))
            return NULL;
        return packets[index];
    }
};

#endif
