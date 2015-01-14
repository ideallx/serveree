#ifndef _DATAUNIT_CMESSAGE_H_
#define _DATAUNIT_CMESSAGE_H_

#include <iop_config.h>
#include "../OSInedependent/others.h"
#include "../../stdafx.h"

#pragma pack(4)

const int MESSAGE_SIZE = 1024;				// ����Package���msgs��

const int MaxTrans = 700;                   // ������HEAD�������
const int MaxFileName = 30;
const int MaxUserInfoOneMessage = 10;
const int MaxSeqsInOnePacket = 50;
const int MaxPackets = 1024;                // ����PACKAGE ������
const int MaxClassInfo = 10;

const int VersionNumber = 1;
const int HeartBeatInterval = 3000;			// ���������
const TS_UINT64 SeqBegin = 1;				// seq��ʼλ�ã�seq��1��ʼ


// �������� ����TS_MESSAGE_HEAD �� TS_MESSAGE_BODY
typedef struct {
    char Body[MESSAGE_SIZE];
} ts_msg, *LPTS_MESSAGE;

// ���͸��ض�ĳ���ͻ���address
typedef struct {
    struct sockaddr_in  peeraddr;
    ts_msg msg;
} TS_PEER_MESSAGE, *LPTS_PEER_MESSAGE;


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


// �ṹ
enum CleanType {
    CleanShowWare =     1,
    CleanHideWare =     2,
    CleanShowClass =    4,
    CleanHideClass =    8,
    CleanScreen =       16,
    CleanCourse =       32,
};

enum MissingType {
    MISS_SINGLE,
    MISS_SERIES,
    MISS_ALL
};

enum GraphicPacketType_t {
    GraphicPacketBeginMove,
    GraphicPacketNormal,
    GraphicPacketPenBrush,
    GraphicPacketEraser,
    GraphicPacketCls,
    GraphicPacketMoveScreen
};

// ���н��
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
    RoleStudent,
    RoleReplay,
};

enum RaceType {
    RaceInit,
    RaceRace,
    RaceResult,
};

enum ReservedUID_t {
    ServerUID,
    AgentUID,
    SelfUID,			// ����
    TeacherUID,
    NobodyUID,          // û����
    CoursewareUID,

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


enum PaintMode {
    PaintNormal,    // as usual
    PaintPPT        // transparent background and covering the ppt
};

// �������ͣ���Ӧ TS_MESSAGE_HEAD.type
enum PacketType {
    PACKETTRANSPORT,		// ���������

    GRAPHICS,				// ͼ��
    COURSEWARE,             // �ļ����μ�
    TEXT,					// ����
    AUDIO,					// ��Ƶ
    VIDEO,					// ��Ƶ
    PICTURE,				// ͼ��
    COMMAND,				// ���ʣ���ˢ���֮��
    SETWRITEAUTH,           // ����ѧ���Ƿ��д
    PLAYERCONTROL,          // ����������
    RACE,                   // ����
    QUESTION,               // ��������

    // packetfix���ϣ�����Զ�����
    PACKETFIX = 40,			// ������
    RESEND,					// �ط�������
    MAXSEQLIST,             // �����б�

    CONNECTION = 49,        // ���������÷�ָ��

    PACKETCONTROL = 50,		// ���ư�
    ENTERCLASS,				// ����༶
    LEAVECLASS,				// �뿪�༶
    HEARTBEAT,				// ������
    USERLIST,				// ��ǰ�û���Ϣ�б�
    ADDUSER,				// �����û�
    REMOVEUSER,				// �����û�

    ENTERAGENT,             // ����agent������
    CREATECLASS,            // ��������
    DESTROYCLASS,           // ���ٿ���
    ALLCLASSINFO,           // ���п�����Ϣ
    CLASSDETAIL,            // ������ϸ��Ϣ

    SCANPORT,				// �˿�ɨ����

};


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

enum QuestionFormat {
    QuestionChoice,         // ѡ��
    QuestionBool,           // �Ƿ�
    QuestionFillBlank,      // ���
    QuestionSubjective,     // ����
};

enum QuestionType {
    QuestionInit,           // �������
    QuestionAnswer,         // �ش�����
    QuestionResult,         // ������
    QuestionStatistics,     // ����ͳ��
};

enum ScoreTableData {
    ScoreCorrect,
    ScoreUncorrect,
    ScoreBlank,
};

enum ChoiceAnswer {
    ChoiceUnset     = 0,
    ChoiceA         = 1,
    ChoiceB         = 2,
    ChoiceC         = 4,
    ChoiceD         = 8,

    ChoiceBoolWall  = 15,
    ChoiceTrue      = 16,
    ChoiceFalse     = 32,

    ChoiceStatistics = 64,
};



typedef struct {
    TS_UINT64 uid;
    TS_UINT64 maxSeq;
} MAXSEQ_UNIT;

// �ļ�
typedef struct {
    DWORD nameLen;
    DWORD fileLen;
    DWORD progress;
    DWORD totalPackets;
    unsigned char filename[MaxFileName];
    unsigned char* filecontent;
} FILE_CONTENT;

typedef struct {
    TS_UINT64 classid;
    TS_UINT64 teacherid;
    unsigned char className[40];    // �γ���
    unsigned char nickname[20];     // ������ʦ�ǳ�~
} CLASS_INFO;

typedef struct {
    TS_UINT64 uid;
    TS_UINT64 reserved;
    TS_UINT64 classid;
    unsigned char role;
    unsigned char isWriteable;
    unsigned char isLoggedIn;
    unsigned char username[20];
} USER_INFO;

// �ϴ����棬�����ǵ���ͼ�ε�
typedef struct {
    DWORD ShapeID;
    WORD ShapeType;
    WORD PageID;
    DWORD BeginPx;		// ͼ�ο�ʼ��
    DWORD BeginPy;
    DWORD PointX;		// ͼ�ε�ǰ��
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
// �ṹ

// ͨ��
// �����壨�ط��������ڱ���ͷ֮��
typedef struct {
    TS_MESSAGE_HEAD head;
    TS_UINT64 missingUID;		// �����������û���UID
    MissingType missingType;
    unsigned short count;		// ����seq����
    TS_UINT64 seq[MaxSeqsInOnePacket];
} RCONNECT;
// ͨ��


// ����
// �½����ý��
typedef struct {
    TS_MESSAGE_HEAD     head;
    WORD                failcode;
    CLASS_INFO          info;
} DOWN_CREATECLASS;

// �û��������б�
typedef struct {
    TS_MESSAGE_HEAD head;
    unsigned short count;		// ������Ԫ��
    MAXSEQ_UNIT unit[MaxSeqsInOnePacket / 2];
} DOWN_MAXSEQ_LIST;

// ���п�����Ϣ
typedef struct {
    TS_MESSAGE_HEAD     head;
    WORD                classNum;
    CLASS_INFO          classes[MaxClassInfo];
} DOWN_ALLCLASSINFO;

// �����û�
typedef struct {
    TS_MESSAGE_HEAD head;
    USER_INFO enterUser;
} SERVER_CLASS_ADD_USER;

// ɾ���û�
typedef struct {
    TS_MESSAGE_HEAD head;
    TS_UINT64 leaveUser;
} SERVER_CLASS_REMOVE_USER;

// �����û��б�
typedef struct {
    TS_MESSAGE_HEAD head;
    int userNumberInMessage;
    USER_INFO users[MaxUserInfoOneMessage];
} SERVER_CLASS_USER_LIST;


// ����༶�ظ�
typedef struct {
    TS_MESSAGE_HEAD head;
    enum MsgResult result;			// ���н��
    enum RoleOfClass role;			// �û���ɫ
    TS_UINT64 uid;					// ����ͻ��˵�UID
    sockaddr_in addr;				// �������˵�ַ
    unsigned char className[40];	// �γ���
    TS_UINT64 lastSeq;              // ��һ���������кţ�����������
} DOWN_AGENTSERVICE;
// ����

// ����
// ����/�뿪����
typedef struct {
    TS_MESSAGE_HEAD head;
    TS_UINT64 classid;				// ��������뿪�Ŀ���ID
    unsigned char username[20];		// �û���
    unsigned char password[20];		// ����
} UP_AGENTSERVICE;

// �½�����
typedef struct {
    TS_MESSAGE_HEAD head;
    unsigned char className[40];    // �γ���
    TS_UINT64 uid;                  // ������ʦID
    unsigned char nickname[20];     // ������ʦ�ǳ�~
    int allowedStudentNum;          // �������ѧ����
} UP_CREATECLASS;

// ���ٿ���
typedef struct {
    TS_MESSAGE_HEAD     head;
    TS_UINT64           classid;
} UP_DESTROYCLASS;

// ������
typedef struct {
    TS_MESSAGE_HEAD head;
    TS_UINT64 maxSeq;
} UP_HEARTBEAT;

// ����ط�
typedef struct {
    TS_MESSAGE_HEAD head;
    TS_UINT64 uid;					// ��ʧ����UID
    TS_UINT64 beginSeq;				// ��ʧ������ʼseq
    TS_UINT64 endSeq;				// ��ʧ������ֹseq(-1Ϊ���µ�seq)
} UP_RESEND_SERIES;
// ����

// ת����Ϣ
// ͼ�ε���
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

// �ļ�����
typedef struct {
    TS_MESSAGE_HEAD head;
    WORD isEnd;
    DWORD totalPackets;
    unsigned char content[MaxTrans];
} TS_FILE_PACKET, *LPTS_FILE_PACKET;

// ����
typedef struct {
    TS_MESSAGE_HEAD head;
    WORD raceType;          // �������ͣ���������/ѧ������/������
    WORD writingTime;       // ������Ĵ���ʱ��
    TS_UINT64 teacherUID;   // ��������Ľ�ʦUID
    TS_UINT64 studentUID;   // �����ѧ��UID/���𵽵�ѧ��
} TS_RACE_PACKET, *LPTS_RACE_PACKET;

// ����дȨ��
typedef struct {
    TS_MESSAGE_HEAD head;
    TS_UINT64 toUID;                // �����Ƶ�UID
    DWORD sceneID;                  // ������UID����Ӧ��SCENEID
    WORD writeable;                 // 1��д��0����д
} SET_USER_WRITE_AUTH;

// ����������
typedef struct {
    TS_MESSAGE_HEAD head;
    unsigned char filename[MaxFileName];
    WORD pa;
    WORD step;
    DWORD toPosition;
    DWORD toSubPosition;
} TS_PLAYER_PACKET;

// ���ⷢ��
typedef struct {
    TS_MESSAGE_HEAD head;
    WORD questionID;                // ���
    WORD qType;                     // ��������
    WORD qFormat;                   // ������ʽ
    WORD time;                      // ����ʱ��
    WORD answer;                    // �������ʱΪ��ȷ�𰸣��ش�ʱΪѧ����
} TS_QUESTION_PACKET;


// ת����Ϣ

// ���ܺ�������ȡһЩ��Ϣ
short packetSize(const ts_msg& p);
TS_UINT64 getSeq(const ts_msg& p);
TS_UINT64 getUid(const ts_msg& p);
enum PacketType getType(const ts_msg& p);
TS_UINT64 getTime(const ts_msg& p);
TS_UINT64 getKey(const ts_msg& p);

#endif
