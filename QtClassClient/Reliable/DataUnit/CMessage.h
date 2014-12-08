#ifndef _DATAUNIT_CMESSAGE_H_
#define _DATAUNIT_CMESSAGE_H_

#include <iop_config.h>
#include "../OSInedependent/others.h"
#include "../../stdafx.h"

#pragma pack(4)

const int MESSAGE_SIZE = 1024;				// 单个Package最大msgs数
const int MaxTrans = 700;                   // 单条除HEAD外最大传输
const int HeartBeatInterval = 5000;			// 心跳包间隔
const TS_UINT64 SeqBegin = 1;				// seq开始位置，seq从1开始
const int MaxFileName = 30;
const int MaxUserInfoOneMessage = 10;

const int VersionNumber = 1;

const int MaxClassInfo = 10;

extern TS_UINT64 globalUID;
extern TS_UINT64 globalTimeDiff;

enum CleanType {
    CleanSceneOnly      = 0,
    CleanShowWare       = 1,
    CleanHideWare       = 2,
    CleanShowClass      = 4,
    CleanHideClass      = 8
};

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

const int MaxSeqsInOnePacket = 50;
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

typedef struct {
    TS_UINT64 uid;
    TS_UINT64 maxSeq;
} MAXSEQ_UNIT;

typedef struct {
    TS_MESSAGE_HEAD head;
    unsigned short count;		// 后续单元数
    MAXSEQ_UNIT unit[MaxSeqsInOnePacket / 2];
} DOWN_MAXSEQ_LIST;


typedef struct {
    TS_MESSAGE_HEAD head;
    int count;
    MAXSEQ_UNIT unit[MaxSeqsInOnePacket];
} ONLINE_LIST;


// 上行报文
typedef struct {
    TS_MESSAGE_HEAD head;
    TS_UINT64 classid;				// 进入或者离开的课堂ID
    unsigned char username[20];		// 用户名
    unsigned char password[20];		// 密码
} UP_AGENTSERVICE;


typedef struct {
    TS_MESSAGE_HEAD head;
    unsigned char className[40];    // 课程名
    TS_UINT64 uid;                  // 开课老师ID
    unsigned char nickname[20];     // 开课老师昵称~
    int allowedStudentNum;          // 最大允许学生数
} UP_CREATECLASS;

typedef struct {
    TS_MESSAGE_HEAD     head;
    WORD                failcode;
    TS_UINT64           classid;
} DOWN_CREATECLASS;

typedef struct {
    TS_MESSAGE_HEAD     head;
    TS_UINT64           classid;
} UP_DESTROYCLASS;

typedef struct {
    TS_UINT64 classid;
    TS_UINT64 teacherid;
    unsigned char className[40];    // 课程名
    unsigned char nickname[20];     // 开课老师昵称~
} CLASS_INFO;

typedef struct {
    TS_MESSAGE_HEAD     head;
    WORD                classNum;
    CLASS_INFO          classes[MaxClassInfo];
} DOWN_ALLCLASSINFO;

typedef struct {
    TS_MESSAGE_HEAD head;
    TS_UINT64 maxSeq;
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
	unsigned char isLoggedIn;
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
    USER_INFO users[MaxUserInfoOneMessage];
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
    BYTE BeginFlag;
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
} TS_GRAPHIC_TOOL_DATA;

typedef struct {
    TS_UINT64 targetUID;
    DWORD shapeID;
    DWORD PointX;
    DWORD PointY;
} TS_GRAPHIC_ERASER;

enum GraphicPacketType_t {
    GraphicPacketBeginMove,
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
        TS_GRAPHIC_TOOL_DATA tool;
        TS_GRAPHIC_ERASER eraser;
    };
} TS_GRAPHIC_PACKET, *LPTS_GRAPHIC_PACKET;

typedef struct {
    TS_MESSAGE_HEAD head;
    WORD isEnd;
    DWORD totalPackets;
    unsigned char content[MaxTrans];
} TS_FILE_PACKET, *LPTS_FILE_PACKET;

typedef struct {
    TS_MESSAGE_HEAD head;
    WORD raceType;          // 答题类型，发起抢答/学生抢答/抢答结果
    WORD writingTime;       // 抢到后的答题时间
    TS_UINT64 teacherUID;   // 发起抢答的教师UID
    TS_UINT64 studentUID;   // 抢答的学生UID/抢答到的学生
} TS_RACE_PACKET, *LPTS_RACE_PACKET;

// 运行结果
enum MsgResult {
    Success,
    SuccessEnterClass,
    SuccessLeaveClass,
    SuccessDownload,

    WarnAlreadyIn,

    ErrorUsername,
    ErrorPassword,
    ErrorUnknown,
	ErrorNoclass,

    FailedPlay,


    ErrorFormat,
    PleaseWaiting,
    ErrorNoResponseFromServer,
    ErrorFileExist,

    NormalCourseLoading,

};

enum RoleOfClass {
    RoleTeacher,
    RoleStudent
};

enum RaceType {
    RaceInit,
    RaceRace,
    RaceResult,
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
    COURSEWARE,             // 文件，课件
    TEXT,					// 文字
    AUDIO,					// 音频
    VIDEO,					// 视频
    PICTURE,				// 图像
    COMMAND,				// 画笔，画刷变更之类
    SETWRITEAUTH,           // 设置学生是否可写
    PLAYERCONTROL,          // 播放器控制
    RACE,                   // 抢答

    PACKETFIX = 40,			// 修正包
    RESEND,					// 重发单个包
    MAXSEQLIST,             // 最大包列表
	
    CONNECTION  = 49,       // 建立连接用废指令

    PACKETCONTROL = 50,		// 控制包
    ENTERCLASS,				// 进入班级
    LEAVECLASS,				// 离开班级
    HEARTBEAT,				// 心跳包
    USERLIST,				// 当前用户信息列表
    ADDUSER,				// 增加用户
    REMOVEUSER,				// 减少用户

    CREATECLASS,            // 创建课堂
    DESTROYCLASS,           // 销毁课堂
    ALLCLASSINFO,           // 所有课堂信息
    CLASSDETAIL,            // 课堂详细信息
	
	SCANPORT,				// 端口扫描用

};

// 功能函数，获取一些信息
short packetSize(const ts_msg& p);
TS_UINT64 getSeq(const ts_msg& p);
TS_UINT64 getUid(const ts_msg& p);
enum PacketType getType(const ts_msg& p);
TS_UINT64 getTime(const ts_msg& p);

enum ReservedUID_t {
    ServerUID,
    AgentUID,
    SelfUID,			// 自身
    TeacherUID,
    NobodyUID,          // 没有人

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


enum PaintMode {
    PaintNormal,    // as usual
    PaintPPT        // transparent background and covering the ppt
};



// 下行报文
typedef struct {
    TS_MESSAGE_HEAD head;
    enum MsgResult result;			// 运行结果
    enum RoleOfClass role;			// 用户角色
    TS_UINT64 uid;					// 给予客户端的UID
    sockaddr_in addr;				// 服务器端地址
    TS_UINT64 lastSeq;              // 上一次最后的序列号，断线重连！
} DOWN_AGENTSERVICE;


typedef struct {
    DWORD nameLen;
    DWORD fileLen;
    DWORD progress;
    DWORD totalPackets;
    unsigned char filename[MaxFileName];
    unsigned char* filecontent;
} FILE_CONTENT;


typedef struct {
    TS_MESSAGE_HEAD head;
    TS_UINT64 toUID;                // 被控制的UID
    DWORD sceneID;                  // 被控制UID所对应的SCENEID
    WORD writeable;                 // 1能写，0不能写
} SET_USER_WRITE_AUTH;

enum PlayerAction {
    ActionStart,
    ActionStop,
    ActionPrev,
    ActionNext,
    ActionPause,
    ActionSubNext,
    ActionSubPrev,
    ActionGoto,
};

typedef struct {
    TS_MESSAGE_HEAD head;
    unsigned char filename[MaxFileName];
    WORD pa;
    WORD step;
    DWORD toPosition;
    DWORD toSubPosition;
} TS_PLAYER_PACKET;

#endif
