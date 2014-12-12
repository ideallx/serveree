#include <string>
#include <iostream>

#include "CBlockManager.h"

CBlockManager::CBlockManager() :
	fileNamePrefix("L") {
	iop_lock_init(&lockUserBlock);
}

CBlockManager::~CBlockManager() {
	iop_lock_destroy(&lockUserBlock);
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
#ifdef _IDEAL_ENV_
	if (uid > 10000)
		return -1;
#endif
	iop_lock(&lockUserBlock);
	CBlock* b = getBlockByUid(uid);
	if (b == NULL) {
		b = new CBlock(uid);
		map_userBlock.insert(make_pair(uid, b));
	}
	iop_unlock(&lockUserBlock);
	b->setFilePrefix(fileNamePrefix);
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
	CBlock* result;
	iop_lock(&lockUserBlock);
	auto iter = map_userBlock.find(uid);
	if (iter != map_userBlock.end()) {
		result = iter->second;
	} else {
		result =  NULL;
	}
	iop_unlock(&lockUserBlock);
	return result;
}

 void CBlockManager::getLostSeqIDs(map<TS_UINT64, set<TS_UINT64> >& results) {
	iop_lock(&lockUserBlock);
	for (auto iter = map_userBlock.begin();
		iter != map_userBlock.end(); iter++) {
		set<TS_UINT64> pids = iter->second->scanMissingPackets();
		if (pids.size() != 0) {
			results.insert(make_pair(iter->first, pids));
		}
	}
	iop_unlock(&lockUserBlock);
}

int CBlockManager::getSavePackage(set<pair<TS_UINT64, CPackage*> >& out) {
	int count = 0;
	iop_lock(&lockUserBlock);
	for (auto iter = map_userBlock.begin(); iter != map_userBlock.end(); ) {
		set<CPackage*> packages;
		iter->second->savePackage(packages);

		for (auto it2 = packages.begin(); it2 != packages.end(); it2++) {
			out.insert(make_pair(iter->first, *it2));
			count++;
		}
		iter++;
	}
	iop_unlock(&lockUserBlock);
	return count;
}

void CBlockManager::removeBlock(TS_UINT64 uid) {
	if ((map_userBlock.count(uid) == 0) || (map_userBlock[uid] == NULL))
		return;

	CBlock* cb = map_userBlock[uid];
	delete cb;
	cb = NULL;
	iop_lock(&lockUserBlock);
	map_userBlock.erase(uid);
	iop_unlock(&lockUserBlock);
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
	iop_lock(&lockUserBlock);
	if (seq == 0) {
		removeBlock(uid);
		CBlock* b = new CBlock(uid);
		b->setFilePrefix(fileNamePrefix);
		map_userBlock.insert(make_pair(uid, b));
	} else {
		map_userBlock[uid]->setMaxSeq(seq);
	}
	iop_unlock(&lockUserBlock);
}

TS_UINT64 CBlockManager::getMaxSeqOfUID(TS_UINT64 uid) {
	TS_UINT64 result = 0;
	iop_lock(&lockUserBlock);
	if ((map_userBlock.count(uid) == 0) || (map_userBlock[uid] == NULL))
		result = 0;
	else
		result = map_userBlock[uid]->getMaxSeq();
	iop_unlock(&lockUserBlock);

	return result;
}
