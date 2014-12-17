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

enum PacketType getType(const ts_msg& p) {
	return static_cast<enum PacketType> (((TS_MESSAGE_HEAD *) &p)->type);
}

TS_UINT64 getTime(const ts_msg& p) {
    return ((TS_MESSAGE_HEAD*) &p)->time;
}
