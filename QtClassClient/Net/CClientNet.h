#pragma once

#include <QDebug>
#include <iop_thread.h>

#include "../Reliable/DataUnit/CMessage.h"
#include "../Message/CMsgObject.h"
#include "../Reliable/Connections/CReliableConnection.h"
#include "../Reliable/DataStructure/TSQueue.h"
#include "../Reliable/DataUnit/UserBase.h"
#include "../Reliable/Server/CServer.h"

// Network Communication Controller
class CClientNet : public CServer, public CMsgObject
{
private:
    CReliableConnection*    m_Connect;			// 本地连接,
    CPeerConnection*        m_agent;
    struct sockaddr_in      m_Addr;
    TS_UINT64               m_seq;              // next seq
    TS_UINT64               m_uid;

    iop_thread_t            pthread_hb;


public:
	CClientNet(void);
	virtual ~CClientNet(void);

    bool scanServer(struct sockaddr_in& result);

public:				
	// 启动网络模块
	bool Start(unsigned short port);

	DWORD MsgHandler(TS_PEER_MESSAGE& pmsg);

	void sendProc();
	void recvProc();
	void msgProc();

	// 发送建立连接信息
	void sendConnectionMsg();

	// 心跳包发送
	void sendHeartBeat();

	// 心跳包开启
	void startupHeartBeat();
    void endHeartBeat();

	void addServerAddr(sockaddr_in in);

public:			
	void ProcessMessage(ts_msg& msg, WPARAM wParam, LPARAM lParam, BOOL isremote);
	void SetServerAddr(DWORD s_code, char* ip, WORD port);
	void SetServerAddr(DWORD s_code, struct sockaddr_in addr);

    void setUID(TS_UINT64 uid);

    inline void setTimeDiff(TS_UINT64 diff) { globalTimeDiff = diff; }

    inline void setBeginSequence(TS_UINT64 seq) { m_seq = seq; }

    inline int loadProgress() { return m_Connect->getLoadingProcess(); }

private:

	void buildSendMessage(ts_msg& msg);

	void MakeIPv4Addr(struct sockaddr_in& addr, char* ip, WORD port);

    // 心跳包过程
    friend thread_ret_type thread_func_call HBProc(LPVOID lpParam);
};
