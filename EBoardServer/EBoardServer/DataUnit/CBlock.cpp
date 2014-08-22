/*
 * CBlock.cpp
 *
 *  Created on: 2014-6-18
 *      Author: root
 */

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

	if (packageNum != curPackageNum) {					// ����ʹ�����һ������ʡȥfind����
		auto iter = blockContents.find(packageNum);
		if (iter != blockContents.end()) {
			curPackageNum = iter->first;
			curPackage = iter->second;
		} else {
			for (auto it2 = blockContents.begin(); it2 != blockContents.end(); it2++) {
				(*it2).second->scanAll();					// �յ�һ����Ҫ�¿�Package������£���֮ǰ�İ�Ӧ��ȫ������
			}
			CPackage* cpa;
			if (isFirstMsg) {								// ����û�У�����һ������һ�������ܲ���0���������pos֮ǰ��miss��
				cpa = new CPackage(pos);
				isFirstMsg = false;
			} else {
				cpa = new CPackage(0);
			}
			blockContents.insert(make_pair(packageNum, cpa));

			curPackageNum = packageNum;
			curPackage = cpa;
		}
	}
	pLen = curPackage->insert(msg, pos);			// �������и�array����ֱ��д��
	cachePrivacy(curPackageNum, *curPackage);

#ifdef _DEBUG_INFO_
	if (pLen <= 0)
		cout << "block: add fail ";
	else
		cout << "block: add OKOK ";
#endif
	return pLen;
}

// �������
void CBlock::cachePrivacy(int packageNum, CPackage& p) {
	if (!p.isFull())									// arrayһ����ֱ��д�ļ�
		return;
	
	p.save(zipName, packageNum, isFirstWrite);
	isFirstWrite = false;
	
	for (auto iter = blockContents.begin(); iter != blockContents.end(); iter++) {
		int pNum = iter->first;
		CPackage *package = iter->second;

		if (packageNum - pNum < 2)						// ��������������ڴ���
			break;
							
		if (iter->second->isFull()) {					// �������arrayǰ�滹������һ��array����
			delete iter->second;
			blockContents.erase(iter);
			break;
		}
	}
}

set<TS_UINT64> CBlock::scanMissingPackets() {
	set<TS_UINT64> answers;			// �������ת���ɵ����к�

	for (auto iter = blockContents.begin(); iter != blockContents.end(); iter++) {	// �Ѱ�
		set<int> results;															// ��ȡ�����λ�ú�
		int answer = (*iter).second->scanMissingPackets(results);					// ��ȡ���ڶ�ʧpacket��λ��
		for (auto i = results.begin(); i != results.end(); i++) {	
			answers.insert(getSequence((*iter).first, (*i)));						// ���ݰ��ţ�λ�úţ��õ����
		}
	}

	return answers;
}

int CBlock::readMsg(TS_UINT64 seq, ts_msg& pout) {
	DWORD packageNum, pos;
	getArrayNumberAndPos(seq, packageNum, pos);
	
	if (packageNum != curPackageNum) {	
		auto iter = blockContents.find(packageNum);
		if (iter != blockContents.end()) {					// ��seq���ڴ淶Χ�ڣ���ȥ�ڴ�����
			curPackage = (*iter).second;
		} else {											// ����ֻ�����ļ�ȥ��
			if (CPackage::testZipFileExist(zipName, packageNum)) {	// �ȳ������ļ��Ƿ����
				CPackage *p = new CPackage;
				p->load(zipName, packageNum);
				blockContents.insert(make_pair(packageNum, p));		// ���ļ����ڳ�����CPackage
				curPackage = p;
			} else {
				return -1;
			}
		}
	}
	return curPackage->query(pout, pos);
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
	for (auto iter = blockContents.begin(); iter != blockContents.end(); iter++) {
		iter->second->save(zipName, iter->first, isFirstWrite);
		isFirstWrite = false;
	}
}