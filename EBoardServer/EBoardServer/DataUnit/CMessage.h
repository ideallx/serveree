#ifndef _DATAUNIT_CMESSAGE_H_
#define _DATAUNIT_CMESSAGE_H_

#include "../Stdafx.h"
#include "../OSInedependent/others.h"

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
const int MaxSeqsInOnePacket = 50;		// ÿ���ط�������ຬ�е����������20���ǲ������˵�

typedef struct {
	TS_MESSAGE_HEAD head;
	int count;
	TS_UINT64 seq[MaxSeqsInOnePacket];
} RCONNECT;

// ���б���
typedef struct {				
	TS_MESSAGE_HEAD head;
	TS_UINT64 classid;				// ��������뿪�Ŀ���ID
	enum RoleOfClass role;			// �û���ɫ
	unsigned char username[20];		// �û���
	unsigned char password[20];		// ����
} UP_AGENTSERVICE;

typedef struct {
	TS_MESSAGE_HEAD head;
} UP_HEARTBEAT;

// ���б���
typedef struct {
	TS_MESSAGE_HEAD head;		
	enum MsgResult result;		// ���н��
	sockaddr_in addr;			// �������˵�ַ
} DOWN_AGENTSERVICE;


// ���н��
enum MsgResult {
	Success,

	WarnAlreadyIn,

	ErrorUserName,
	ErrorUserPassword
};

enum RoleOfClass {
	RoleTeacher,
	RoleStudent
};


// �������� ����TS_MESSAGE_HEAD �� TS_MESSAGE_BODY
typedef struct {
	char Body[MESSAGE_SIZE];
} ts_msg, *LPTS_MESSAGE;

// ���͸��ض�ĳ���ͻ���address
typedef struct {
	struct sockaddr_in  peeraddr;
	ts_msg msg;
} TS_PEER_MESSAGE, *LPTS_PEER_MESSAGE;

// �������ͣ���Ӧ TS_MESSAGE_HEAD.type
enum PacketType {
	PACKETTRANSPORT,		// ���������
	GRAPHICS,
	TEXT,
	AUDIO,
	VIDEO,
	PICTURE,
	COMMAND,

	PACKETFIX = 40,			// ������
	RESEND,

	PACKETCONTROL = 50,		// ���ư�
	ENTERCLASS,
	LEAVECLASS,
	HEARTBEAT
};

// ���ܺ�������ȡһЩ��Ϣ
short packetSize(const ts_msg& p);
TS_UINT64 getSeq(const ts_msg& p);
TS_UINT64 getUid(const ts_msg& p);
enum PacketType getType(const ts_msg& p);
int buildResentMessage(ts_msg& tempMsg, const char *msg, int bodyLen);

enum ReservedUID_t {
	ServerUID,
	AgentUID,

	ReservedUID = 50	// 50֮ǰ��UIDȫ������
};

#endif