#ifndef _DATAUNIT_CMESSAGE_H_
#define _DATAUNIT_CMESSAGE_H_

#include "StdAfx.h"

#pragma pack(4)

const int MESSAGE_SIZE = 1024;

// 报文头
typedef struct {
	TS_UINT64 UID;				// 8 Bytes 用户ID
	unsigned int sequence;		// 4 Bytes 报文流水号

	unsigned char type;			// 1 Bytes 消息类型
	unsigned char isEnd;		// 1 Bytes 是否是最后一部分
	
	TS_UINT64 SID;				// 8 Bytes 会话ID
	TS_UINT64 time;				// 8 Bytes 时间戳

	TS_UINT64 reserved;			// 8 Bytes 保留
	unsigned char version;		// 1 Bytes 协议版本号
	unsigned short size;		// 2 Bytes 整条长度
} TS_MESSAGE_HEAD;

// 报文体（重发类型）。跟在报文头之后
const int MaxSeqsInOnePacket = 20;		// 每个重发包中最多含有的序号数量
typedef struct {
	int size;
	TS_UINT64 seq[MaxSeqsInOnePacket];
} RCONNECT;

// 报文整体 包括TS_MESSAGE_HEAD 和 TS_MESSAGE_BODY
typedef struct {
	char Body[MESSAGE_SIZE];
} ts_msg, *LPTS_MESSAGE;


// 发送给特定某个客户端address
//typedef struct {
//	struct sockaddr_in  peeraddr;
//	ts_msg			msg;
//} TS_PEER_MESSAGE, *LPTS_PEER_MESSAGE;

typedef struct {
	TS_MESSAGE_HEAD head;
	int data;
} DATA, *LPDATA;


// 报文类型，对应 TS_MESSAGE_HEAD.type
enum PackageType {
	GRAPHICS,
	TEXT,
	AUDIO,
	VIDEO,
	PICTURE,
	COMMAND,
	RCONNECTION
};

// 功能函数，获取一些信息
short packetSize(const ts_msg& p);
TS_UINT64 getSeq(const ts_msg& p);
TS_UINT64 getUid(const ts_msg& p);
enum PackageType getType(const ts_msg& p);
int buildResentMessage(ts_msg& tempMsg, const char *msg, int bodyLen);


#endif