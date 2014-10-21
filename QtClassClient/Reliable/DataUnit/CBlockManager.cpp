#include <string>
#include <iostream>

#include "CBlockManager.h"

CBlockManager::CBlockManager() :
	fileNamePrefix("L") {
}

CBlockManager::~CBlockManager() {
	for (auto iter = map_userBlock.begin(); 
		iter != map_userBlock.end(); ++iter) {
		DESTROY(iter->second);
	}
	map_userBlock.clear();
}

int CBlockManager::readRecord(TS_UINT64 uid, TS_UINT64 seq, ts_msg& p) {
	if (seq == 0)
		return -1;
	CBlock* b = getBlockByUid(uid);
	if (NULL == b)
		return -1;

	return b->readMsg(seq, p);
}

int CBlockManager::record(ts_msg& in) {
	TS_UINT64 uid = getUid(in);
	CBlock* b = getBlockByUid(uid);
	if (b == NULL) {
		b = new CBlock(uid);
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

int CBlockManager::getSavePackage(set<pair<TS_UINT64, CPackage*> >& out) {
	int count = 0;
	for (auto iter = map_userBlock.begin(); iter != map_userBlock.end(); ) {
		set<CPackage*> packages;
		iter->second->savePackage(packages);

		for (auto it2 = packages.begin(); it2 != packages.end(); it2++) {
			out.insert(make_pair(iter->first, *it2));
			count++;
		}
		iter++;
	}
	return count;
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

void CBlockManager::setMaxSeqOfUid(TS_UINT64 uid, TS_UINT64 seq) {
    if ((map_userBlock.count(uid) == 0) || (map_userBlock[uid] == NULL))
        return;
    map_userBlock[uid]->setMaxSeq(seq);
}

TS_UINT64 CBlockManager::getMaxSeqOfUID(TS_UINT64 uid) {
	if ((map_userBlock.count(uid) == 0) || (map_userBlock[uid] == NULL))
		return 0;
	return map_userBlock[uid]->getMaxSeq();
}
