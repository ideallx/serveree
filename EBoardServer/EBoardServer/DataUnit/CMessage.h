#ifndef _DATAUNIT_CMESSAGE_H_
#define _DATAUNIT_CMESSAGE_H_

#include "../Stdafx.h"
#include "../OSInedependent/others.h"

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
const int MaxSeqsInOnePacket = 50;		// 每个重发包中最多含有的序号数量，20个是不是少了点

typedef struct {
	TS_MESSAGE_HEAD head;
	int count;
	TS_UINT64 seq[MaxSeqsInOnePacket];
} RCONNECT;

// 上行报文
typedef struct {				
	TS_MESSAGE_HEAD head;
	TS_UINT64 classid;				// 进入或者离开的课堂ID
	enum RoleOfClass role;			// 用户角色
	unsigned char username[20];		// 用户名
	unsigned char password[20];		// 密码
} UP_AGENTSERVICE;

typedef struct {
	TS_MESSAGE_HEAD head;
} UP_HEARTBEAT;

// 下行报文
typedef struct {
	TS_MESSAGE_HEAD head;		
	enum MsgResult result;		// 运行结果
	sockaddr_in addr;			// 服务器端地址
} DOWN_AGENTSERVICE;


// 运行结果
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


// 报文整体 包括TS_MESSAGE_HEAD 和 TS_MESSAGE_BODY
typedef struct {
	char Body[MESSAGE_SIZE];
} ts_msg, *LPTS_MESSAGE;

// 发送给特定某个客户端address
typedef struct {
	struct sockaddr_in  peeraddr;
	ts_msg msg;
} TS_PEER_MESSAGE, *LPTS_PEER_MESSAGE;

// 报文类型，对应 TS_MESSAGE_HEAD.type
enum PacketType {
	PACKETTRANSPORT,		// 正常传输包
	GRAPHICS,
	TEXT,
	AUDIO,
	VIDEO,
	PICTURE,
	COMMAND,

	PACKETFIX = 40,			// 修正包
	RESEND,

	PACKETCONTROL = 50,		// 控制包
	ENTERCLASS,
	LEAVECLASS,
	HEARTBEAT
};

// 功能函数，获取一些信息
short packetSize(const ts_msg& p);
TS_UINT64 getSeq(const ts_msg& p);
TS_UINT64 getUid(const ts_msg& p);
enum PacketType getType(const ts_msg& p);
int buildResentMessage(ts_msg& tempMsg, const char *msg, int bodyLen);

enum ReservedUID_t {
	ServerUID,
	AgentUID,

	ReservedUID = 50	// 50之前的UID全部保留
};

#endif