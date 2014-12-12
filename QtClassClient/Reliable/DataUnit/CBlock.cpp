#include <string>
#include <iostream>

#include "CBlock.h"
#include "../OSInedependent/others.h"

CBlock::CBlock(TS_UINT64 uid) :
    curPackage(NULL),			// 缓存上一次被调用的包
	_uid(uid),					// 用户id
	fileNamePrefix("L"),		// 随便给个初始值
    maxSeq(0),
    maxPackageNum(0) {
	iop_lock_init(&mapLock);
	iop_lock_init(&packageLock);
	straDestroy = new CDestroyStrategy();
	straWrite = new CWriteFileStrategy();
}

CBlock::~CBlock() {
	clear();
	iop_lock_destroy(&mapLock);
	iop_lock_destroy(&packageLock);
}

void CBlock::clear() {
	for (auto iter = blockContents.begin(); iter != blockContents.end();) {
		DESTROY(iter->second);
		iter++;
	}
	blockContents.clear();
}

CPackage* CBlock::createNewPackage(int packageNum) {
    CPackage* cpa = new CPackage;
    cpa->setID(packageNum);

    if (packageNum > maxPackageNum)
        maxPackageNum = packageNum;

    // cout << _uid << " new " << packageNum << endl;

    // blockContents.insert(make_pair(packageNum, curPackage));	// 新package加入map中
    straDestroy->onMsgAddStrategy(curPackage);					// 新package加入销毁等待。
	return cpa;
}

int CBlock::addMsg(const ts_msg& msg) {
	int pLen = -1;

	DWORD packageNum, pos;
	TS_UINT64 seq = getSeq(msg);

	if (0 == seq) {
		return -1;
	}

	getArrayNumberAndPos(seq, packageNum, pos);			// 获取package号，msg在package的位置

    if (seq > maxSeq)
        maxSeq = seq;

    //if (maxPackageNum <= packageNum) {                  // 如果最大包属于package3 那么预先创建package4
    //    cout << "postion 1" << endl;
    //    createNewPackage(packageNum + 1);
    //}

	if (curPackage == NULL || packageNum != curPackage->getID()) {	// 若是使用最近一个包，省去find步骤
		bool isNewPackage = false;
		iop_lock(&mapLock);								// 怕重复new
		auto findPackage = blockContents.find(packageNum);
		if (findPackage == blockContents.end()) {
			cout << _uid << " new " << packageNum << " " << seq << endl;
			curPackage = createNewPackage(packageNum);
			blockContents.insert(make_pair(packageNum, curPackage));
			isNewPackage = true;
		} else {
			curPackage = findPackage->second;
		}
		iop_unlock(&mapLock);

		if (isNewPackage) {
			for (auto exPackage = blockContents.begin(); exPackage != blockContents.end(); exPackage++) {
				if (exPackage->first < packageNum)			// 收到一个需要新开Package的情况下，那之前的包应该全部收满
					exPackage->second->needAll();
			}
		}
	}
	iop_lock(&packageLock);
	pLen = curPackage->insert(msg, pos);			// 若是已有该array，则直接写入
	iop_unlock(&packageLock);

#ifdef _DEBUG_INFO_
	if (pLen <= 0)
        cout << "block: add " << seq << " fail ";
	else
        cout << "block: add " << seq << " okok ";
#endif
	return pLen;
}

set<TS_UINT64> CBlock::scanMissingPackets() {
	set<TS_UINT64> answers;			// 将数组号转换成的序列号
	
	for (auto iter = blockContents.begin(); iter != blockContents.end();) {		// 搜包
		set<int> results;														// 获取保存的位置号
		CPackage* pack = iter->second;
		if (pack->isFull()) {
			straWrite->onMsgScanStrategy(pack);									// 写文件扫描触发

			if (straDestroy->onMsgScanStrategy(pack)) {							// 销毁包扫描触发
				iop_lock(&packageLock);
				if (curPackage == iter->second)
					curPackage = NULL;
				delete iter->second;											// 若返回true则销毁
                cout << "delete " << iter->first << endl;
				iter->second = NULL;
				iop_unlock(&packageLock);

				iop_lock(&mapLock);
				blockContents.erase(iter++);
				iop_unlock(&mapLock);

			} else {
				iter++;
			}
		} else {
            pack->scanMissingPackets(results);                                  // 获取包内丢失packet的位置
			for (auto i = results.begin(); i != results.end(); i++) {	
				answers.insert(getSequence(iter->first, (*i)));					// 根据包号，位置号，得到序号
			}
			iter++;
		}
	}
	return answers;
}

int CBlock::readMsg(TS_UINT64 seq, ts_msg& pout) {
	DWORD packageNum, pos;
	getArrayNumberAndPos(seq, packageNum, pos);
	
	if (curPackage == NULL || packageNum != curPackage->getID()) {
		auto iter = blockContents.find(packageNum);
		if (iter != blockContents.end()) {							// 若seq在内存范围内，则去内存中找
			curPackage = iter->second;
		} else {													// 不行只能找文件去了
			string zipName = fileNamePrefix + "_" + int2string(_uid) + ".zip";
			if (CPackage::isZipFileExist(zipName, packageNum)) {	// 先尝试找文件是否存在
				CPackage *p = new CPackage;
				p->load(zipName, packageNum);
				p->setID(packageNum);
				p->setSaved(true);

				iop_lock(&mapLock);
				blockContents.insert(make_pair(packageNum, p));		// 从文件里挖出来的CPackage
				iop_unlock(&mapLock);

				curPackage = p;
				straWrite->onMsgAddStrategy(p);						// 加入销毁策略
			} else {
				return -1;
			}
		}
	}
	iop_lock(&packageLock);
	int result = curPackage->query(pout, pos);
	iop_unlock(&packageLock);
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
		straWrite->onMsgAddStrategy(iter->second);
		iter++;
	}
	iop_unlock(&mapLock);
}

void CBlock::setMaxSeq(TS_UINT64 seq) {
    maxSeq = seq;
	// TODO
}
