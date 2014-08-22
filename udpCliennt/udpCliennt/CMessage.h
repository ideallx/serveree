#ifndef _DATAUNIT_CMESSAGE_H_
#define _DATAUNIT_CMESSAGE_H_

#include "StdAfx.h"

#pragma pack(4)

const int MESSAGE_SIZE = 1024;

// ����ͷ
typedef struct {
	TS_UINT64 UID;				// 8 Bytes �û�ID
	unsigned int sequence;		// 4 Bytes ������ˮ��

	unsigned char type;			// 1 Bytes ��Ϣ����
	unsigned char isEnd;		// 1 Bytes �Ƿ������һ����
	
	TS_UINT64 SID;				// 8 Bytes �ỰID
	TS_UINT64 time;				// 8 Bytes ʱ���

	TS_UINT64 reserved;			// 8 Bytes ����
	unsigned char version;		// 1 Bytes Э��汾��
	unsigned short size;		// 2 Bytes ��������
} TS_MESSAGE_HEAD;

// �����壨�ط����ͣ������ڱ���ͷ֮��
const int MaxSeqsInOnePacket = 20;		// ÿ���ط�������ຬ�е��������
typedef struct {
	int size;
	TS_UINT64 seq[MaxSeqsInOnePacket];
} RCONNECT;

// �������� ����TS_MESSAGE_HEAD �� TS_MESSAGE_BODY
typedef struct {
	char Body[MESSAGE_SIZE];
} ts_msg, *LPTS_MESSAGE;


// ���͸��ض�ĳ���ͻ���address
//typedef struct {
//	struct sockaddr_in  peeraddr;
//	ts_msg			msg;
//} TS_PEER_MESSAGE, *LPTS_PEER_MESSAGE;

typedef struct {
	TS_MESSAGE_HEAD head;
	int data;
} DATA, *LPDATA;


// �������ͣ���Ӧ TS_MESSAGE_HEAD.type
enum PackageType {
	GRAPHICS,
	TEXT,
	AUDIO,
	VIDEO,
	PICTURE,
	COMMAND,
	RCONNECTION
};

// ���ܺ�������ȡһЩ��Ϣ
short packetSize(const ts_msg& p);
TS_UINT64 getSeq(const ts_msg& p);
TS_UINT64 getUid(const ts_msg& p);
enum PackageType getType(const ts_msg& p);
int buildResentMessage(ts_msg& tempMsg, const char *msg, int bodyLen);


#endif