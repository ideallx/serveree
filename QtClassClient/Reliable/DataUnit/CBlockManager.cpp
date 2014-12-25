#include <string>
#include <iostream>
#include <iop_util.h>

#include "CBlockManager.h"

CBlockManager::CBlockManager() 
	: fileNamePrefix("L")
	, lastBlock(NULL) {
	iop_lock_init(&lockUserBlock);
}

CBlockManager::~CBlockManager() {
    saveAllBlocks();
	iop_lock_destroy(&lockUserBlock);
	for (auto iter = map_userBlock.begin(); 
		iter != map_userBlock.end(); ++iter) {
		DESTROY(iter->second);
	}
	map_userBlock.clear();
}

int getUidFromFileName(string filename) {
    int i = filename.find_last_of('_');
    int j = filename.find_last_of('.');
    string result = filename.substr(i + 1, j - i - 1);
    return atoi(result.c_str());
}

#include <direct.h>
#include <io.h>
set<TS_UINT64> CBlockManager::loadExistFile(string prefix) {
    set<TS_UINT64> result;
    struct _finddata_t fileinfo;
    long handle;
    string stringpattern = prefix + "*.zip";
    handle = _findfirst(stringpattern.c_str(), &fileinfo);
	if (handle < 0)
        return result;

    TS_UINT64 uid = getUidFromFileName(string(fileinfo.name));
    if (uid > 0) {
        setBlock(uid, fileinfo.name);
        result.insert(uid);
    }

    while (!_findnext(handle, &fileinfo)) {
        TS_UINT64 uid = getUidFromFileName(string(fileinfo.name));
        if (uid > 0) {
            setBlock(uid, fileinfo.name);
            result.insert(uid);
        }
    }

    return result;
}

void CBlockManager::setBlock(TS_UINT64 uid, string blockfilename) {
    iop_lock(&lockUserBlock);
    CBlock* b = getBlockByUid(uid);
    if (b == NULL) {
        b = new CBlock(uid);
        map_userBlock.insert(make_pair(uid, b));
        cout << "create new block for " << uid << endl;
    }
    iop_unlock(&lockUserBlock);

    cout << uid << endl;
}

TS_UINT64 CBlockManager::loadPackage(TS_UINT64 uid, int packageNum, CPackage& package) {
    iop_lock(&lockUserBlock);
    CBlock* b = getBlockByUid(uid);
    iop_unlock(&lockUserBlock);
    b->setFilePrefix(fileNamePrefix);

    return b->loadFromFile(packageNum, package);
}

int CBlockManager::readRecord(TS_UINT64 uid, TS_UINT64 seq, ts_msg& p) {
	if (seq == 0)
		return -1;

	iop_lock(&lockUserBlock);
	CBlock* b = getBlockByUid(uid);
	iop_unlock(&lockUserBlock);

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
		cout << "create new block for " << uid << endl;
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

	if (NULL != lastBlock && lastBlock->uid() == uid)
		return lastBlock;

	auto iter = map_userBlock.find(uid);
	if (iter != map_userBlock.end()) {
		result = iter->second;
	} else {
		result =  NULL;
	}
	lastBlock = result;

	return result;
}

 void CBlockManager::getLostSeqIDs(map<TS_UINT64, set<TS_UINT64> >& results) {
	iop_lock(&lockUserBlock);
	for (auto iter = map_userBlock.begin();
		iter != map_userBlock.end(); iter++) {
		set<TS_UINT64> pids = iter->second->scanMissingPackets();
		if (!pids.empty()) {
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

void CBlockManager::saveAllBlocks() {
    for (auto iter = map_userBlock.begin(); iter != map_userBlock.end(); ++iter) {
        saveBlock(iter->first);
    }
}

void CBlockManager::setMaxSeqOfUid(TS_UINT64 uid, TS_UINT64 seq) {
    if ((map_userBlock.count(uid) == 0) || (map_userBlock[uid] == NULL))
        return;
	iop_lock(&lockUserBlock);
	if (seq == 0) {
		removeBlock(uid);
		CBlock* b = new CBlock(uid);
		cout << "reset block for uid:" << uid << endl;
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
