#ifndef _DATAUNIT_CMESSAGE_H_
#define _DATAUNIT_CMESSAGE_H_

#include "../OSInedependent/others.h"

#pragma pack(4)

const int MESSAGE_SIZE = 1024;				// 单个Package最大msgs数
const int HeartBeatInterval = 10000;		// 心跳包间隔
const TS_UINT64 SeqBegin = 1;				// seq开始位置，seq从1开始

const int VersionNumber = 1;

extern TS_UINT64 globalUID;

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

    DWORD subSeq;               // 4 Bytes 子序号
} TS_MESSAGE_HEAD, *LPTS_MESSAGE_HEAD;

// 报文体（重发类型）。跟在报文头之后

const int MaxSeqsInOnePacket = 50;		// 每个重发包中最多含有的序号数量，20个是不是少了点
enum MissingType {
    MISS_SINGLE,
    MISS_SERIES,
    MISS_ALL
};

typedef struct {
    TS_MESSAGE_HEAD head;
    TS_UINT64 missingUID;		// 丢包所属的用户的UID
    MissingType missingType;
    unsigned short count;		// 后续seq个数
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
    unsigned char username[20];		// 用户名
    unsigned char password[20];		// 密码
    sockaddr_in addr;				// 服务器地址
} UP_ENTERAGENT;

typedef struct {
    TS_MESSAGE_HEAD head;
} UP_HEARTBEAT;

typedef struct {
    TS_MESSAGE_HEAD head;
    TS_UINT64 uid;					// 丢失包的UID
    TS_UINT64 beginSeq;				// 丢失包的起始seq
    TS_UINT64 endSeq;				// 丢失包的终止seq(-1为最新的seq)
} UP_RESEND_SERIES;

typedef struct {
    TS_UINT64 uid;
    TS_UINT64 reserved;
    TS_UINT64 classid;
    unsigned char role;
    unsigned char username[20];
} USER_INFO;

typedef struct {
    TS_MESSAGE_HEAD head;
    USER_INFO enterUser;
} SERVER_CLASS_ADD_USER;

typedef struct {
    TS_MESSAGE_HEAD head;
    TS_UINT64 leaveUser;
} SERVER_CLASS_REMOVE_USER;

typedef struct {
    TS_MESSAGE_HEAD head;
    int userNumberInMessage;
    USER_INFO users[10];
} SERVER_CLASS_USER_LIST;


// 上传画面，可能是点阵，图形等
typedef struct {
    DWORD ShapeID;
    WORD ShapeType;
    WORD PageID;
    DWORD BeginPx;		// 图形开始点
    DWORD BeginPy;
    DWORD PointX;		// 图形当前点
    DWORD PointY;
    BYTE DoneFlag;
    BYTE Alpha;
} TS_GRAPHIC_DATA;

typedef struct {
    WORD penid;
    WORD penR;
    WORD penG;
    WORD penB;
    WORD penWidth;
    WORD brushid;
    WORD brushR;
    WORD brushG;
    WORD brushB;
} TS_PENBRUSH_DATA;


enum GraphicPacketType_t {
    GraphicPacketEndMove,
    GraphicPacketNormal,
    GraphicPacketPenBrush,
    GraphicPacketEraser,
    GraphicPacketCls,
    GraphicPacketMoveScreen
};


typedef struct {
    TS_MESSAGE_HEAD head;
    WORD graphicsType;
    DWORD SceneID;
    union {
        TS_GRAPHIC_DATA data;
        TS_PENBRUSH_DATA penbrush;
    };
} TS_GRAPHIC_PACKET, *LPTS_GRAPHIC_PACKET;

// 下行报文
typedef struct {
    TS_MESSAGE_HEAD head;
    enum MsgResult result;			// 运行结果
    sockaddr_in addr;				// 服务器端地址
} DOWN_AGENTSERVICE;


// 运行结果
enum MsgResult {
    Success,
    SuccessEnterClass,
    SuccessLeaveClass,

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

    GRAPHICS,				// 图案
    TEXT,					// 文字
    AUDIO,					// 音频
    VIDEO,					// 视频
    PICTURE,				// 图像
    COMMAND,				// 画笔，画刷变更之类

    PACKETFIX = 40,			// 修正包
    RESEND,					// 重发单个包

    PACKETCONTROL = 50,		// 控制包
    ENTERCLASS,				// 进入班级
    LEAVECLASS,				// 离开班级
    ENTERAGENT,				// 登录Agent服务器
    HEARTBEAT,				// 心跳包
    USERLIST,				// 当前用户信息列表
    ADDUSER,				// 增加用户
    REMOVEUSER				// 减少用户
};

// 功能函数，获取一些信息
short packetSize(const ts_msg& p);
TS_UINT64 getSeq(const ts_msg& p);
TS_UINT64 getUid(const ts_msg& p);
enum PacketType getType(const ts_msg& p);

enum ReservedUID_t {
    ServerUID,
    AgentUID,
    SelfUID,			// 自身
    TeacherUID,

    ReservedUID = 50	// 50之前的UID全部保留
};

enum ShapeType {
    NONE,
    SCRIPTS,
    LINE,
    RECTANGLE,
    ELLIPSE,
    ROUNDRECT,
    HEXAGON,
    TRIANGLE,
    IMAGE,
};

#endif
