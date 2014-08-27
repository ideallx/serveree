#include <string>
#include "CBlockManager.h"
#include <iostream>
extern string int2string(TS_UINT64);

CBlockManager::CBlockManager() {
	struct timeval tv;
	gettimeofday(&tv, NULL);
	classid = static_cast<TS_UINT64> (tv.tv_sec);
}

CBlockManager::~CBlockManager() {
	for (auto iter = map_userBlock.begin(); 
		iter != map_userBlock.end(); ++iter) {
		DESTROY(iter->second);
	}
	map_userBlock.clear();
}

int CBlockManager::readRecord(TS_UINT64 uid, TS_UINT64 seq, ts_msg& p) {
	CBlock* b = getBlockByUid(uid);
	if (NULL == b)
		return -1;

	return b->readMsg(seq, p);
}

int CBlockManager::record(ts_msg& in, int size) {
	TS_UINT64 uid = getUid(in);
	CBlock* b = getBlockByUid(uid);
	if (b == NULL) {
		b = new CBlock();

		struct timeval tv;
		gettimeofday(&tv, NULL);
		TS_UINT64 time = static_cast<TS_UINT64> (tv.tv_sec);

		b->setZipName(int2string(classid) + "_"
			+ int2string(time) + "_"
			+ int2string(uid) + ".zip");

		map_userBlock.insert(make_pair(uid, b));
	}

	int result = b->addMsg(in);
#ifdef _DEBUG_INFO_
	if (result <= 0)
		cout << "bm: add fail " << endl;
	else
		cout << "bm: add OKOK " << endl;
#endif
	return result;
}

CBlock* CBlockManager::getBlockByUid(TS_UINT64 uid) {
	auto iter = map_userBlock.find(uid);
	if (iter != map_userBlock.end()) {
		return iter->second;
	} else {
		return NULL;
	}
}

map<TS_UINT64, set<TS_UINT64> > CBlockManager::getLostSeqIDs() {
	map<TS_UINT64, set<TS_UINT64> > results;
	for (auto iter = map_userBlock.begin();
		iter != map_userBlock.end(); iter++) {
		set<TS_UINT64> pids = iter->second->scanMissingPackets();
		if (pids.size() != 0) {
			results.insert(make_pair(iter->first, pids));
		}
	}
	return results;
}

void CBlockManager::removeBlock(TS_UINT64 uid) {
	if ((map_userBlock.count(uid) == 0) || (map_userBlock[uid] == NULL))
		return;

	CBlock* cb = map_userBlock[uid];
	delete cb;
	cb = NULL;
	map_userBlock.erase(uid);
}

void CBlockManager::saveBlock(TS_UINT64 uid) {
	if ((map_userBlock.count(uid) == 0) || (map_userBlock[uid] == NULL))
		return;
	
	CBlock* cb = map_userBlock[uid];
	cb->saveAll();
}