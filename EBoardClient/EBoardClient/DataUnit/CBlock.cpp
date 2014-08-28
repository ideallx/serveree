#include <string>
#include <sstream>
#include <iostream>

#include "CBlock.h"
#include "../OSInedependent/others.h"

string int2string(TS_UINT64 number) {
	stringstream ss;
	string s;
	ss << number;
	ss >> s;
	return s;
}

CBlock::CBlock() :
	isFirstWrite(true),
	zipName("Z"),
	curPackage(NULL),
	curPackageNum(-1),
	isFirstMsg(true) {
	iop_lock_init(&mapLock);
}

CBlock::~CBlock() {
	clear();
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
	getArrayNumberAndPos(getSeq(msg), packageNum, pos);	// ��ȡarray�ţ�array��ַ

	iop_lock(&mapLock);
	if (packageNum != curPackageNum) {					// ����ʹ�����һ������ʡȥfind����
		auto iter = blockContents.find(packageNum);
		if (iter != blockContents.end()) {
			curPackageNum = iter->first;
			curPackage = iter->second;
		} else {
			for (auto it2 = blockContents.begin(); it2 != blockContents.end(); it2++) {
				it2->second->scanAll();					// �յ�һ����Ҫ�¿�Package������£���֮ǰ�İ�Ӧ��ȫ������
			}
			CPackage* cpa;
			if (isFirstMsg) {							// ����û�У�����һ������һ�������ܲ���0���������pos֮ǰ��miss��
				cpa = new CPackage(pos);
				isFirstMsg = false;
			} else {
				cpa = new CPackage(0);
			}

			curPackageNum = packageNum;
			curPackage = cpa;
			
			blockContents.insert(make_pair(curPackageNum, curPackage));
			blockHp.insert(make_pair(curPackageNum, initialHP));
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
		int answer = iter->second->scanMissingPackets(results);					// ��ȡ���ڶ�ʧpacket��λ��
		if (iter->second->isFull()) {
			iter->second->save(zipName, iter->first, isFirstWrite);				// CPackageһ������ļ�
			isFirstWrite = false;

			int hp = blockHp[iter->first]--;
			if (0 == hp) {														// �Ƿ���ڴ���ɾ������HP������
				//delete iter->second;
				//iter->second = NULL;
				blockHp.erase(iter->first);
				blockContents.erase(iter++);
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

int CBlock::readMsg(TS_UINT64 seq, ts_msg& pout) {
	DWORD packageNum, pos;
	getArrayNumberAndPos(seq, packageNum, pos);
	
	iop_lock(&mapLock);
	if (packageNum != curPackageNum) {	
		auto iter = blockContents.find(packageNum);
		if (iter != blockContents.end()) {							// ��seq���ڴ淶Χ�ڣ���ȥ�ڴ�����
			curPackage = iter->second;
		} else {													// ����ֻ�����ļ�ȥ��
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
	packageNum = static_cast<DWORD> ((seq - 1) / MaxPackets);
	pos = static_cast<DWORD> ((seq - 1) % MaxPackets);
}

TS_UINT64 CBlock::getSequence(int packageNum, int pos) {
	return packageNum * MaxPackets + pos + 1;
}

void CBlock::saveAll() {
	iop_lock(&mapLock);
	for (auto iter = blockContents.begin(); iter != blockContents.end(); iter++) {
		iter->second->save(zipName, iter->first, isFirstWrite);
		isFirstWrite = false;
	}
	iop_unlock(&mapLock);
}

// ����true�� ��ȫ����
// ����false����;���ļ�û��������
bool CBlock::getMsgs(set<ts_msg*>& out, TS_UINT64 beg, TS_UINT64 end) {
	ts_msg* msg = new ts_msg();
	for (TS_UINT64 i = beg; i < end; i++) {
		int result = readMsg(i, *msg);
		if (result < 0)
			break;
		out.insert(msg);
	}
	delete msg;
	return true;
}