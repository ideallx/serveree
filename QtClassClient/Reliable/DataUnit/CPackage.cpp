#include <assert.h>

#include <iostream>
#include <fstream>

#include "CPackage.h"
#include "../DataUnit/CMessage.h"
#include "../Zip/myzip.h"

CPackage::CPackage(int beginPos) :
	scanHead(beginPos),
	packageID(0),
	_isSaved(false) {
	init();
}

CPackage::~CPackage() {
	unInit();
}

void CPackage::init() {
	memset(packets, 0, MaxPackets * sizeof(void*));

}

void CPackage::unInit() {
	clearPackets();
}

void CPackage::clearPackets() {
	for (int i = 0; i < MaxPackets; i++) {
		if (NULL != packets[i]) { 
			free(packets[i]);
			packets[i] = NULL; 
		}
	}
}

int CPackage::insert(const ts_msg& p, int pos) {
	if (!isAvailable(pos) || isExist(pos)) {	// 若是该seq异常，或者已经收到过，返回false
#ifdef _DEBUG_INFO_
		cout << "P: add fail " << getSeq(p) << " " ;
#endif
		return -1;
	}
	
	int size = packetSize(p);

	ts_msg* msg = (ts_msg*) malloc(size);	// 自己创建内存
	memcpy(msg, &p, size);					// 保存住传进来的msg
	packets[pos] = msg;						// 加入数组

	if (pos == scanHead) {
		scanHead = pos + 1;
	} else if (pos > scanHead) {
		for (int i = scanHead; i < pos; i++)
			missing.insert(i);				// 缺失的包加到set中
		scanHead = pos + 1;
	} else if (pos < scanHead) {
		missing.erase(pos);					// 获得的包从set中取出
	}
#ifdef _DEBUG_INFO_
	cout << "P: add OKOK ";
#endif
	return size;
}

int CPackage::query(ts_msg& pout, int pos) {
	if (!isAvailable(pos) || !isExist(pos))
		return -1;
	
	ts_msg* packet = packets[pos];
	int size = packetSize(*packet);

	memcpy((void*) &pout, packet, size);
	return size;
}

int CPackage::scanMissingPackets(set<int>& out) {
	if (missing.size() == 0)
		return 0;

	out.insert(missing.begin(), missing.end());
	return missing.size();
}

// scanHead之前的miss的package，都已经保存进了missing set中
// 现在需要needAll，只要把scanHead到MaxPackets中所有包都加到missing中
void CPackage::needAll() {
	for (int i = scanHead; i < MaxPackets; i++) {
		missing.insert(i);
	}
	scanHead = MaxPackets;
}

bool CPackage::save(string fileName, bool isCreate) {
	if (isZipFileExist(fileName, packageID))			// 若文件已经存在，不用重复保存
		return true;

	char *content = (char *) malloc(MESSAGE_SIZE * MaxPackets);
	for (int i = 0; i < scanHead; i++) {
		ts_msg* msg = packets[i];
		if (NULL == msg)
			continue;
		int size = packetSize(*msg);
		if ((size > MESSAGE_SIZE) || size < sizeof(TS_MESSAGE_HEAD))
			continue;

		memcpy(content + i * MESSAGE_SIZE, msg, size);
	}
	if (!CZip::saveToZip(fileName.c_str(), int2string(packageID).c_str(), 
		content, (scanHead) * MESSAGE_SIZE, isCreate)) {
#ifdef _DEBUG_INFO_
			cout << "Save File Error" << endl;
#endif
			return false;
	}
	// cout << isCreate?"1":"0";
	// cout << "save " << packageID << endl;
	free(content);
	_isSaved = true;
	return true;
}

bool CPackage::isZipFileExist(string fileName, int packageNum) {
	int length = CZip::getOriginalSize(fileName.c_str(), 
		int2string(packageNum).c_str());					// 文件大小
	if (length == 0)
		return false;
	return true;
}

bool CPackage::load(string fileName, int packageNum) {
	clearPackets();

	int length = CZip::getOriginalSize(fileName.c_str(), 
		int2string(packageNum).c_str());					// 文件大小
	if (length == 0)
		return false;

	char *content = (char *) malloc(length);
	bool result = CZip::loadFromZip(fileName.c_str(), 
		int2string(packageNum).c_str(), content, length);	// 文件是否可以打开

	if (result == false)									// 文件打不开，回复false
		return false;

	length /= MESSAGE_SIZE;

	for (int i = 0; i < length; i++) { 
		char* temp = content + i * MESSAGE_SIZE;
		int size = packetSize(*(ts_msg*) temp);
		if ((size > MESSAGE_SIZE) || (size < sizeof(TS_MESSAGE_HEAD)))	// 尺寸错误
			continue;

		ts_msg* msg = (ts_msg*) malloc(size);	// 自己创建内存
		if (NULL == msg) {						// 内存不足
			clearPackets();						// 放弃创建
			break;
		}
		memcpy(msg, temp, size);				// 保存住传进来的msg
		packets[i] = msg;

		scanHead = i + 1;
	}

	free(content);
	_isSaved = true;
	return true;
}

bool CPackage::isExist(int pos) {
	if (!isAvailable(pos)) {
		return false;
	}
	return packets[pos] != NULL;
}
