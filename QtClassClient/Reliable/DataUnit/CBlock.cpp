#include <string>
#include <iostream>

#include "CBlock.h"
#include "../OSInedependent/others.h"

CBlock::CBlock(TS_UINT64 uid) :
    curPackage(NULL),			// ������һ�α����õİ�
	_uid(uid),					// �û�id
	fileNamePrefix("L"),		// ��������ʼֵ
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

    // blockContents.insert(make_pair(packageNum, curPackage));	// ��package����map��
    straDestroy->onMsgAddStrategy(curPackage);					// ��package�������ٵȴ���
	return cpa;
}

int CBlock::addMsg(const ts_msg& msg) {
	int pLen = -1;

	DWORD packageNum, pos;
	TS_UINT64 seq = getSeq(msg);

	if (0 == seq) {
		return -1;
	}

	getArrayNumberAndPos(seq, packageNum, pos);			// ��ȡpackage�ţ�msg��package��λ��

    if (seq > maxSeq)
        maxSeq = seq;

    //if (maxPackageNum <= packageNum) {                  // �����������package3 ��ôԤ�ȴ���package4
    //    cout << "postion 1" << endl;
    //    createNewPackage(packageNum + 1);
    //}

	if (curPackage == NULL || packageNum != curPackage->getID()) {	// ����ʹ�����һ������ʡȥfind����
		bool isNewPackage = false;
		iop_lock(&mapLock);								// ���ظ�new
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
				if (exPackage->first < packageNum)			// �յ�һ����Ҫ�¿�Package������£���֮ǰ�İ�Ӧ��ȫ������
					exPackage->second->needAll();
			}
		}
	}
	iop_lock(&packageLock);
	pLen = curPackage->insert(msg, pos);			// �������и�array����ֱ��д��
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
	set<TS_UINT64> answers;			// �������ת���ɵ����к�
	
	for (auto iter = blockContents.begin(); iter != blockContents.end();) {		// �Ѱ�
		set<int> results;														// ��ȡ�����λ�ú�
		CPackage* pack = iter->second;
		if (pack->isFull()) {
			straWrite->onMsgScanStrategy(pack);									// д�ļ�ɨ�败��

			if (straDestroy->onMsgScanStrategy(pack)) {							// ���ٰ�ɨ�败��
				iop_lock(&packageLock);
				if (curPackage == iter->second)
					curPackage = NULL;
				delete iter->second;											// ������true������
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
            pack->scanMissingPackets(results);                                  // ��ȡ���ڶ�ʧpacket��λ��
			for (auto i = results.begin(); i != results.end(); i++) {	
				answers.insert(getSequence(iter->first, (*i)));					// ���ݰ��ţ�λ�úţ��õ����
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
		if (iter != blockContents.end()) {							// ��seq���ڴ淶Χ�ڣ���ȥ�ڴ�����
			curPackage = iter->second;
		} else {													// ����ֻ�����ļ�ȥ��
			string zipName = fileNamePrefix + "_" + int2string(_uid) + ".zip";
			if (CPackage::isZipFileExist(zipName, packageNum)) {	// �ȳ������ļ��Ƿ����
				CPackage *p = new CPackage;
				p->load(zipName, packageNum);
				p->setID(packageNum);
				p->setSaved(true);

				iop_lock(&mapLock);
				blockContents.insert(make_pair(packageNum, p));		// ���ļ����ڳ�����CPackage
				iop_unlock(&mapLock);

				curPackage = p;
				straWrite->onMsgAddStrategy(p);						// �������ٲ���
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

// ��ֻ�ܵ�seq�϶���Ϊ0�ˡ�
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
