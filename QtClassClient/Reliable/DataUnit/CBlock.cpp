#include <string>
#include <iostream>

#include "CBlock.h"
#include "../OSInedependent/others.h"

CBlock::CBlock(TS_UINT64 uid) :
    curPackage(NULL),			// ������һ�α����õİ�
	_uid(uid),					// �û�id
	fileNamePrefix("L"),		// ��������ʼֵ
	maxSeq(0) {					
	iop_lock_init(&mapLock);
	straDestroy = new CDestroyStrategy();
	straWrite = new CWriteFileStrategy();
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
	getArrayNumberAndPos(seq, packageNum, pos);			// ��ȡpackage�ţ�msg��package��λ��

	iop_lock(&mapLock);
	if (curPackage == NULL || packageNum != curPackage->getID()) {	// ����ʹ�����һ������ʡȥfind����
		auto iter = blockContents.find(packageNum);
		if (iter != blockContents.end()) {				// ��map���ҵ�package
			curPackage = iter->second;
		} else {
			for (auto it2 = blockContents.begin(); it2 != blockContents.end(); it2++) {
				it2->second->needAll();					// �յ�һ����Ҫ�¿�Package������£���֮ǰ�İ�Ӧ��ȫ������
			}

            CPackage* cpa = new CPackage;
			curPackage = cpa;
			cpa->setID(packageNum);
			blockContents.insert(make_pair(packageNum, curPackage));	// ��package����map��

			straDestroy->onMsgAddStrategy(curPackage);						// ��package�������ٵȴ���
		}
	}
	pLen = curPackage->insert(msg, pos);			// �������и�array����ֱ��д��
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
	set<TS_UINT64> answers;			// �������ת���ɵ����к�
	
	iop_lock(&mapLock);
	for (auto iter = blockContents.begin(); iter != blockContents.end();) {		// �Ѱ�
		set<int> results;														// ��ȡ�����λ�ú�
		CPackage* pack = iter->second;
		if (pack->isFull()) {
			straWrite->onMsgScanStrategy(pack);									// д�ļ�ɨ�败��

			if (straDestroy->onMsgScanStrategy(pack)) {							// ���ٰ�ɨ�败��
				delete iter->second;											// ������true������
				iter->second = NULL;
				blockContents.erase(iter++);
			} else {
				iter++;
			}
		} else {
			int answer = pack->scanMissingPackets(results);						// ��ȡ���ڶ�ʧpacket��λ��
			for (auto i = results.begin(); i != results.end(); i++) {	
				answers.insert(getSequence(iter->first, (*i)));					// ���ݰ��ţ�λ�úţ��õ����
			}
			iter++;
		}
	}

	iop_unlock(&mapLock);
	return answers;
}

int CBlock::readMsg(TS_UINT64 seq, ts_msg& pout) {
	DWORD packageNum, pos;
	getArrayNumberAndPos(seq, packageNum, pos);
	
	iop_lock(&mapLock);
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
				blockContents.insert(make_pair(packageNum, p));		// ���ļ����ڳ�����CPackage
				curPackage = p;
				straWrite->onMsgAddStrategy(p);						// �������ٲ���
			} else {
				return -1;
			}
		}
	}
	int result = curPackage->query(pout, pos);
	iop_unlock(&mapLock);
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
    // TODO
}
