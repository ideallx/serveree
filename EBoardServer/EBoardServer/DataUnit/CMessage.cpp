#include "CMessage.h"


short packetSize(const ts_msg& p) {
	return ((TS_MESSAGE_HEAD*) &p)->size;
}

TS_UINT64 getSeq(const ts_msg& p) {
	return ((TS_MESSAGE_HEAD*) &p)->sequence;
}

TS_UINT64 getUid(const ts_msg& p) {
	return ((TS_MESSAGE_HEAD*) &p)->UID;
}

enum PackageType getType(const ts_msg& p) {
	return static_cast<enum PackageType> (((TS_MESSAGE_HEAD *) &p)->type);
}

int buildResentMessage(ts_msg& tempMsg, const char *msg, int bodyLen) {
	TS_MESSAGE_HEAD *head = (TS_MESSAGE_HEAD *) &tempMsg;

	struct timeval tv;
	gettimeofday(&tv, NULL);

	head->type = RESEND;
	head->time = static_cast<TS_UINT64> (tv.tv_sec);
	head->size = sizeof(TS_MESSAGE_HEAD) + bodyLen;

	memcpy((char*) &tempMsg + sizeof(TS_MESSAGE_HEAD), msg, bodyLen);
	return head->size;
}
