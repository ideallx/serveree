#include "common.h"

TS_UINT64 sequence;

int generateNormalMsg(ts_msg& msg, TS_UINT64 uid) {
	// ���ݳ�����100-400֮��
	// int length = rand() % 300 + 100;

	// ���ݳ�����525-1024֮��
	int length = rand() % 500 + 525;

	TS_MESSAGE_HEAD* head = (TS_MESSAGE_HEAD*) &msg;
	head->size = length;
	head->sequence = sequence;
	head->isEnd = 0;
	head->UID = uid;
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
	int length = CZip::getOriginalSize(zipName.c_str(), 
		int2string(fileName).c_str());				// �ļ���С

	if (length == 0)				// �ļ��򲻿����ظ�false
		return false;

	return true;
}