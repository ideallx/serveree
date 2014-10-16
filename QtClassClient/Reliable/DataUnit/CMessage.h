#ifndef _DATAUNIT_CMESSAGE_H_
#define _DATAUNIT_CMESSAGE_H_

#include "../OSInedependent/others.h"

#pragma pack(4)

const int MESSAGE_SIZE = 1024;				// ����Package���msgs��
const int HeartBeatInterval = 10000;		// ���������
const TS_UINT64 SeqBegin = 1;				// seq��ʼλ�ã�seq��1��ʼ

const int VersionNumber = 1;

extern TS_UINT64 globalUID;

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

    DWORD subSeq;               // 4 Bytes �����
} TS_MESSAGE_HEAD, *LPTS_MESSAGE_HEAD;

// �����壨�ط����ͣ������ڱ���ͷ֮��

const int MaxSeqsInOnePacket = 50;		// ÿ���ط�������ຬ�е����������20���ǲ������˵�
enum MissingType {
    MISS_SINGLE,
    MISS_SERIES,
    MISS_ALL
};

typedef struct {
    TS_MESSAGE_HEAD head;
    TS_UINT64 missingUID;		// �����������û���UID
    MissingType missingType;
    unsigned short count;		// ����seq����
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
    unsigned char username[20];		// �û���
    unsigned char password[20];		// ����
    sockaddr_in addr;				// ��������ַ
} UP_ENTERAGENT;

typedef struct {
    TS_MESSAGE_HEAD head;
} UP_HEARTBEAT;

typedef struct {
    TS_MESSAGE_HEAD head;
    TS_UINT64 uid;					// ��ʧ����UID
    TS_UINT64 beginSeq;				// ��ʧ������ʼseq
    TS_UINT64 endSeq;				// ��ʧ������ֹseq(-1Ϊ���µ�seq)
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


// �ϴ����棬�����ǵ���ͼ�ε�
typedef struct {
    DWORD ShapeID;
    WORD ShapeType;
    WORD PageID;
    DWORD BeginPx;		// ͼ�ο�ʼ��
    DWORD BeginPy;
    DWORD PointX;		// ͼ�ε�ǰ��
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

// ���б���
typedef struct {
    TS_MESSAGE_HEAD head;
    enum MsgResult result;			// ���н��
    sockaddr_in addr;				// �������˵�ַ
} DOWN_AGENTSERVICE;


// ���н��
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

    GRAPHICS,				// ͼ��
    TEXT,					// ����
    AUDIO,					// ��Ƶ
    VIDEO,					// ��Ƶ
    PICTURE,				// ͼ��
    COMMAND,				// ���ʣ���ˢ���֮��

    PACKETFIX = 40,			// ������
    RESEND,					// �ط�������

    PACKETCONTROL = 50,		// ���ư�
    ENTERCLASS,				// ����༶
    LEAVECLASS,				// �뿪�༶
    ENTERAGENT,				// ��¼Agent������
    HEARTBEAT,				// ������
    USERLIST,				// ��ǰ�û���Ϣ�б�
    ADDUSER,				// �����û�
    REMOVEUSER				// �����û�
};

// ���ܺ�������ȡһЩ��Ϣ
short packetSize(const ts_msg& p);
TS_UINT64 getSeq(const ts_msg& p);
TS_UINT64 getUid(const ts_msg& p);
enum PacketType getType(const ts_msg& p);

enum ReservedUID_t {
    ServerUID,
    AgentUID,
    SelfUID,			// ����
    TeacherUID,

    ReservedUID = 50	// 50֮ǰ��UIDȫ������
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
