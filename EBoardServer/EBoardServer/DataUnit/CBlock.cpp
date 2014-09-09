#include <string>
#include <iostream>

#include "CBlock.h"
#include "../OSInedependent/others.h"

CBlock::CBlock(TS_UINT64 uid) :
	curPackage(NULL),			// 缓存上一次被调用的包
	curPackageNum(-1),			// 上一次被调用的包号
	isFirstMsg(true),			// 是不是第一次收到msg，第一个包号非0会做特殊处理
	_uid(uid),					// 用户id
	fileNamePrefix("L"),		// 随便给个初始值
	maxSeq(0) {					
	iop_lock_init(&mapLock);
}

CBlock::~CBlock() {
	clear();
	iop_lock_destroy(&mapLock);
}

void CBlock::clear() {
	for (auto iter = blockContents.begin(); iter != blockContents.end();) {
		DESTROY(iter->second);
		iter++;
	}
	blockContents.clear();
}

int CBlock::addMsg(const ts_msg& msg) {
	int pLen = -1;

	DWORD packageNum, pos;
	TS_UINT64 seq = getSeq(msg);
	if (seq > maxSeq)
		maxSeq = seq;
	getArrayNumberAndPos(seq, packageNum, pos);			// 获取package号，msg在package的位置

	iop_lock(&mapLock);
	if (packageNum != curPackageNum) {					// 若是使用最近一个包，省去find步骤
		curPackageNum = packageNum;

		auto iter = blockContents.find(packageNum);
		if (iter != blockContents.end()) {				// 在map中找到package
			curPackage = iter->second;
		} else {
			for (auto it2 = blockContents.begin(); it2 != blockContents.end(); it2++) {
				it2->second->needAll();					// 收到一个需要新开Package的情况下，那之前的包应该全部收满
			}

			CPackage* cpa;
			if (isFirstMsg) {							// 若是没有，创建一个，第一个包可能不是0，这里忽略pos之前的miss包
				cpa = new CPackage(pos);
				isFirstMsg = false;
			} else {
				cpa = new CPackage(0);
			}
			curPackage = cpa;
			cpa->setID(curPackageNum);
			
			blockContents.insert(make_pair(curPackageNum, curPackage));	// 新package加入map中
			blockHp.insert(make_pair(curPackageNum, initialHP));		// 新package开始减血
		}
	}
	pLen = curPackage->insert(msg, pos);			// 若是已有该array，则直接写入
	iop_unlock(&mapLock);

#ifdef _DEBUG_INFO_
	if (pLen <= 0)
		cout << "block: add fail ";
	else
		cout << "block: add okok ";
#endif
	return pLen;
}

set<TS_UINT64> CBlock::scanMissingPackets() {
	set<TS_UINT64> answers;			// 将数组号转换成的序列号
	
	iop_lock(&mapLock);
	for (auto iter = blockContents.begin(); iter != blockContents.end();) {		// 搜包
		set<int> results;														// 获取保存的位置号
		CPackage* pack = iter->second;
		int answer = pack->scanMissingPackets(results);							// 获取包内丢失packet的位置
		if (pack->isFull()) {
			if (!pack->isSaved()) {
				saveList.insert(pack);
				pack->setSaved(true);
			}
			int hp = blockHp[iter->first]--;
			if (0 == hp) {														// 是否从内存中删除按照HP来决定
				delete iter->second;
				iter->second = NULL;
				blockHp.erase(iter->first);
				blockContents.erase(iter++);
				curPackageNum = -1;												// 撤销的包号，因为可能curPackage被销毁了。
			} else
				iter++;
		} else {
			for (auto i = results.begin(); i != results.end(); i++) {	
				answers.insert(getSequence(iter->first, (*i)));					// 根据包号，位置号，得到序号
			}
			iter++;
		}
	}
	iop_unlock(&mapLock);
	return answers;
}

int CBlock::savePackage(set<CPackage*>& out) {
	out.insert(saveList.begin(), saveList.end());
	int result = saveList.size();
	saveList.clear();
	return result;
}

int CBlock::readMsg(TS_UINT64 seq, ts_msg& pout) {
	DWORD packageNum, pos;
	getArrayNumberAndPos(seq, packageNum, pos);
	
	iop_lock(&mapLock);
	if (packageNum != curPackageNum) {	
		curPackageNum = packageNum;
		auto iter = blockContents.find(packageNum);
		if (iter != blockContents.end()) {							// 若seq在内存范围内，则去内存中找
			curPackage = iter->second;
		} else {													// 不行只能找文件去了
			string zipName = fileNamePrefix + "_" + int2string(_uid) + ".zip";
			if (CPackage::isZipFileExist(zipName, packageNum)) {	// 先尝试找文件是否存在
				CPackage *p = new CPackage;
				p->load(zipName, packageNum);
				blockContents.insert(make_pair(packageNum, p));		// 从文件里挖出来的CPackage
				blockHp.insert(make_pair(packageNum, initialHP));	// 重新加满血
				curPackage = p;
			} else {
				return -1;
			}
		}
	}
	int result = curPackage->query(pout, pos);
	iop_unlock(&mapLock);
	return result;
}

// 我只能当seq肯定不为0了。
void CBlock::getArrayNumberAndPos(TS_UINT64 seq, DWORD& packageNum, DWORD& pos) {
	if (0 == seq || -1 == seq)
		seq = maxSeq;
	packageNum = static_cast<DWORD> ((seq - SeqBegin) / MaxPackets);
	pos = static_cast<DWORD> ((seq - SeqBegin) % MaxPackets);
}

TS_UINT64 CBlock::getSequence(int packageNum, int pos) {
	return packageNum * MaxPackets + pos + 1;
}

void CBlock::saveAll() {
	iop_lock(&mapLock);
	for (auto iter = blockContents.begin(); iter != blockContents.end(); ) {
		saveList.insert(iter->second);
		iter++;
	}
	iop_unlock(&mapLock);
}

// 返回加入set的msg数量
// end = -1 至今所有的包
int CBlock::getMsgs(set<ts_msg*>& out, TS_UINT64 beg, TS_UINT64 end) {
	ts_msg* msg = new ts_msg();
	if (-1 == end)
		end = maxSeq;

	int count = 0;
	for (TS_UINT64 i = beg; i <= end; i++) {
		int result = readMsg(i, *msg);
		if (result > 0) {
			out.insert(msg);
			count++;
		}
	}
	delete msg;
	return count;
}