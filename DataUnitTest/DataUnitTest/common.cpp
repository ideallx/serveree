#include "common.h"
#include <myzip.h>

TS_UINT64 sequence;

int generateNormalMsg(ts_msg& msg) {
	// 数据长度在100-400之间
	// int length = rand() % 300 + 100;

	// 数据长度在525-1024之间
	int length = rand() % 500 + 525;

	TS_MESSAGE_HEAD* head = (TS_MESSAGE_HEAD*) &msg;
	head->size = length;
	head->sequence = sequence;
	head->isEnd = 0;
	head->UID = 0x01010101;
	head->version = 1;

	char* body = (char *) &msg + sizeof(TS_MESSAGE_HEAD);
	// memset(body,  sequence, length - sizeof(TS_MESSAGE_HEAD));
	int begin = sizeof(TS_MESSAGE_HEAD);
	for (int i = begin; i < length; i++) {
		msg.Body[i] = rand() % 256;
	}
	sequence++;
	return length;
}

extern string int2string(TS_UINT64);

bool checkFileExist(string zipName, int fileName) {
	char temp[20];
	int length = CZip::getOriginalSize(zipName.c_str(), 
		int2string(fileName).c_str());				// 文件大小
	//bool result = CZip::loadFromZip(zipName.c_str(), 
	//	int2string(fileName).c_str(), temp, 20);	// 文件是否可以打开

	if (length == 0)				// 文件打不开，回复false
		return false;

	return true;
}