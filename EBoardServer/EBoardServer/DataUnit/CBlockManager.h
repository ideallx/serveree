#ifndef _DATAUNIT_BLOCKMANAGER_H_
#define _DATAUNIT_BLOCKMANAGER_H_

#include <map>
#include <set>

#include "CBlock.h"
#include "../Stdafx.h"

class CBlockManager {
private:
	map<TS_UINT64, CBlock*> map_userBlock;		// �����û���Ӧ��Block
	string fileNamePrefix;						// ������ļ�����ǰ׺

public:
	CBlockManager();
	virtual ~CBlockManager();

	// ��ĳ���û���ĳ����¼
	int readRecord(TS_UINT64 uid, TS_UINT64 seq, ts_msg& p);

	// ��¼һ����¼
	int record(ts_msg& in);

	// ��ȡÿ��User���ж�ʧ�İ������
	map<TS_UINT64, set<TS_UINT64> > getLostSeqIDs();

	// �Ƴ�Block
	void removeBlock(TS_UINT64 uid);

	// ����Block
	void saveBlock(TS_UINT64 uid);

	// ��ȡ��Ҫ�����CPackage
	int getSavePackage(set<pair<TS_UINT64, CPackage*> >& out);

	// �����ļ���ǰ׺ fprefix_uid.zip/packageNum
	void setFilePrefix(string fprefix) { fileNamePrefix = fprefix; }

	// ��ȡÿ���û����еİ�
	int getAllMsgs(set<ts_msg*>& out);

private:
	CBlock* getBlockByUid(TS_UINT64 uid);

};

#endif