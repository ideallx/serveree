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
	getArrayNumberAndPos(getSeq(msg), packageNum, pos);	// 获取array号，array地址

	if (packageNum != curPackageNum) {					// 若是使用最近一个包，省去find步骤
		auto iter = blockContents.find(packageNum);
		if (iter != blockContents.end()) {
			curPackageNum = iter->first;
			curPackage = iter->second;
		} else {
			for (auto it2 = blockContents.begin(); it2 != blockContents.end(); it2++) {
				(*it2).second->scanAll();					// 收到一个需要新开Package的情况下，那之前的包应该全部收满
			}
			CPackage* cpa;
			if (isFirstMsg) {								// 若是没有，创建一个，第一个包可能不是0，这里忽略pos之前的miss包
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
	pLen = curPackage->insert(msg, pos);			// 若是已有该array，则直接写入
	cachePrivacy(curPackageNum, *curPackage);

#ifdef _DEBUG_INFO_
	if (pLen <= 0)
		cout << "block: add fail ";
	else
		cout << "block: add OKOK ";
#endif
	return pLen;
}

// 缓存机制
void CBlock::cachePrivacy(int packageNum, CPackage& p) {
	if (!p.isFull())									// array一满，直接写文件
		return;
	
	p.save(zipName, packageNum, isFirstWrite);
	isFirstWrite = false;
	
	for (auto iter = blockContents.begin(); iter != blockContents.end(); iter++) {
		int pNum = iter->first;
		CPackage *package = iter->second;

		if (packageNum - pNum < 2)						// 最近几个包留在内存中
			break;
							
		if (iter->second->isFull()) {					// 若是这个array前面还有至少一个array已满
			delete iter->second;
			blockContents.erase(iter);
			break;
		}
	}
}

set<TS_UINT64> CBlock::scanMissingPackets() {
	set<TS_UINT64> answers;			// 将数组号转换成的序列号

	for (auto iter = blockContents.begin(); iter != blockContents.end(); iter++) {	// 搜包
		set<int> results;															// 获取保存的位置号
		int answer = (*iter).second->scanMissingPackets(results);					// 获取包内丢失packet的位置
		for (auto i = results.begin(); i != results.end(); i++) {	
			answers.insert(getSequence((*iter).first, (*i)));						// 根据包号，位置号，得到序号
		}
	}

	return answers;
}

int CBlock::readMsg(TS_UINT64 seq, ts_msg& pout) {
	DWORD packageNum, pos;
	getArrayNumberAndPos(seq, packageNum, pos);
	
	if (packageNum != curPackageNum) {	
		auto iter = blockContents.find(packageNum);
		if (iter != blockContents.end()) {					// 若seq在内存范围内，则去内存中找
			curPackage = (*iter).second;
		} else {											// 不行只能找文件去了
			if (CPackage::testZipFileExist(zipName, packageNum)) {	// 先尝试找文件是否存在
				CPackage *p = new CPackage;
				p->load(zipName, packageNum);
				blockContents.insert(make_pair(packageNum, p));		// 从文件里挖出来的CPackage
				curPackage = p;
			} else {
				return -1;
			}
		}
	}
	return curPackage->query(pout, pos);
}

// 我只能当seq肯定不为0了。
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