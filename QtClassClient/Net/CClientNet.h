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
	CReliableConnection* m_Connect;			// ��������,
	CPeerConnection*	 m_agent;
	struct sockaddr_in	 m_Addr;
    TS_UINT64			 m_seq;             // next seq
	TS_UINT64			 m_uid;

	DWORD				 m_timeDiff;		// �������˺Ϳͻ��˵�ʱ���


public:
	CClientNet(void);
	virtual ~CClientNet(void);

public:				
	// ��������ģ��
	bool Start(unsigned short port);

	DWORD MsgHandler(TS_PEER_MESSAGE& pmsg);

	void sendProc();
	void recvProc();
	void msgProc();
	
	// ����������
	friend void* HBProc(LPVOID lpParam);

	// ����������
	void sendHeartBeat();

	// ����������
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
