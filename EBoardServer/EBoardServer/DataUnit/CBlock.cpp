#include <string>
#include <iostream>

#include "CBlock.h"
#include "../OSInedependent/others.h"

CBlock::CBlock(TS_UINT64 uid) :
	curPackage(NULL),			// ������һ�α����õİ�
	curPackageNum(-1),			// ��һ�α����õİ���
	isFirstMsg(true),			// �ǲ��ǵ�һ���յ�msg����һ�����ŷ�0�������⴦��
	_uid(uid),					// �û�id
	fileNamePrefix("L"),		// ��������ʼֵ
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
	getArrayNumberAndPos(seq, packageNum, pos);			// ��ȡpackage�ţ�msg��package��λ��

	iop_lock(&mapLock);
	if (packageNum != curPackageNum) {					// ����ʹ�����һ������ʡȥfind����
		curPackageNum = packageNum;

		auto iter = blockContents.find(packageNum);
		if (iter != blockContents.end()) {				// ��map���ҵ�package
			curPackage = iter->second;
		} else {
			for (auto it2 = blockContents.begin(); it2 != blockContents.end(); it2++) {
				it2->second->needAll();					// �յ�һ����Ҫ�¿�Package������£���֮ǰ�İ�Ӧ��ȫ������
			}

			CPackage* cpa;
			if (isFirstMsg) {							// ����û�У�����һ������һ�������ܲ���0���������pos֮ǰ��miss��
				cpa = new CPackage(pos);
				isFirstMsg = false;
			} else {
				cpa = new CPackage(0);
			}
			curPackage = cpa;
			cpa->setID(curPackageNum);
			
			blockContents.insert(make_pair(curPackageNum, curPackage));	// ��package����map��
			blockHp.insert(make_pair(curPackageNum, initialHP));		// ��package��ʼ��Ѫ
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
		int answer = pack->scanMissingPackets(results);							// ��ȡ���ڶ�ʧpacket��λ��
		if (pack->isFull()) {
			if (!pack->isSaved()) {
				saveList.insert(pack);
				pack->setSaved(true);
			}
			int hp = blockHp[iter->first]--;
			if (0 == hp) {														// �Ƿ���ڴ���ɾ������HP������
				delete iter->second;
				iter->second = NULL;
				blockHp.erase(iter->first);
				blockContents.erase(iter++);
				curPackageNum = -1;												// �����İ��ţ���Ϊ����curPackage�������ˡ�
			} else
				iter++;
		} else {
			for (auto i = results.begin(); i != results.end(); i++) {	
				answers.insert(getSequence(iter->first, (*i)));					// ���ݰ��ţ�λ�úţ��õ����
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
		if (iter != blockContents.end()) {							// ��seq���ڴ淶Χ�ڣ���ȥ�ڴ�����
			curPackage = iter->second;
		} else {													// ����ֻ�����ļ�ȥ��
			string zipName = fileNamePrefix + "_" + int2string(_uid) + ".zip";
			if (CPackage::isZipFileExist(zipName, packageNum)) {	// �ȳ������ļ��Ƿ����
				CPackage *p = new CPackage;
				p->load(zipName, packageNum);
				blockContents.insert(make_pair(packageNum, p));		// ���ļ����ڳ�����CPackage
				blockHp.insert(make_pair(packageNum, initialHP));	// ���¼���Ѫ
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
		saveList.insert(iter->second);
		iter++;
	}
	iop_unlock(&mapLock);
}

// ���ؼ���set��msg����
// end = -1 �������еİ�
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