#pragma once

#include <QDebug>

#include "../Message/CMsgObject.h"

#include "../Reliable/Connections/CReliableConnection.h"
#include "../Reliable/DataStructure/TSQueue.h"
#include "../Reliable/DataUnit/UserBase.h"
#include "../Reliable/Server/CServer.h"

// Network Communication Controller
class CClientNet : public CServer, public CMsgObject
{
private:
	CReliableConnection* m_Connect;			// 本地连接,
	CPeerConnection*	 m_agent;
	struct sockaddr_in	 m_Addr;
    TS_UINT64			 m_seq;             // next seq
	TS_UINT64			 m_uid;

	DWORD				 m_timeDiff;		// 服务器端和客户端的时间差


public:
	CClientNet(void);
	virtual ~CClientNet(void);

public:				
	// 启动网络模块
	bool Start(unsigned short port);

	DWORD MsgHandler(TS_PEER_MESSAGE& pmsg);

	void sendProc();
	void recvProc();
	void msgProc();
	
	// 心跳包过程
	friend void* HBProc(LPVOID lpParam);

	// 心跳包发送
	void sendHeartBeat();

	// 心跳包开启
	void startupHeartBeat();

	void addServerAddr(sockaddr_in in);

public:			
	void ProcessMessage(ts_msg& msg, WPARAM wParam, LPARAM lParam, BOOL isremote);
	void SetServerAddr(DWORD s_code, char* ip, WORD port);
	void SetServerAddr(DWORD s_code, struct sockaddr_in addr);

    inline void setTimeDiff(DWORD diff) { m_timeDiff = diff; }

private:

	void buildSendMessage(ts_msg& msg);

	void MakeIPv4Addr(struct sockaddr_in& addr, char* ip, WORD port);
};
