#pragma once

#include "../stdafx.h"
#include "CMsgObject.h"

#include "../../../EBoardServer/EBoardServer/Connections/CReliableConnection.h"
#include "../../../EBoardServer/EBoardServer/DataStructure/TSQueue.h"
#include "../../../EBoardServer/EBoardServer/DataUnit/UserBase.h"
#include "../../../EBoardServer/EBoardServer/Server/CServer.h"

// Network Communication Controller
class CClientNet : public CServer, public CMsgObject
{
private:
	CReliableConnection* m_Connect;			// 本地连接,
	CPeerConnection*	 m_agent;
	struct sockaddr_in	 m_Addr;
	TS_UINT64			 m_seq;
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

	inline void addServerAddr(sockaddr_in in) { m_Connect->addPeer(ServerUID, in); }

public:			
	void ProcessMessage(ts_msg& msg, WPARAM wParam, LPARAM lParam, BOOL isremote);
	void SetServerAddr(DWORD s_code, char* ip, WORD port);
	void SetServerAddr(DWORD s_code, struct sockaddr_in addr);

private:

	void buildSendMessage(ts_msg& msg);

	void MakeIPv4Addr(struct sockaddr_in& addr, char* ip, WORD port);
};