#pragma once

#include "../stdafx.h"
#include "CMessageObject.h"
#include "../../../EBoardServer/EBoardServer/Connections/CReliableConnection.h"

// Network Communication Controller
class CClientNet : public CMessageObject
{
private:
	CReliableConnection	m_Connect;					// 本地连接,
	struct sockaddr_in	m_Addr;
	BOOL				m_bIsStart;					// 接收线程的控制

public:
	CClientNet(void){
		m_bIsStart	= FALSE;
	};
	virtual ~CClientNet(void){
		Stop();										// 如果没有停止则先停止数据服务
		Sleep(100);									// 等待子线程退出

		m_CSConnect.Delete();						// 连接销毁
		m_HSConnect.Delete();
		m_WAConnect.Delete();
		m_WSConnect.Delete();

		m_Connect.Delete();								// 本源地址，最后删除
	};

public:				// 启动网络模块
	BOOL Start(void){
		if (m_bIsStart)									// 已经运行
			return TRUE;

		if (!m_Connect.Create()){						// 启动本地连接
			return FALSE;
		}
		else{
			m_CSConnect.Copy(&m_Connect);				// 服务器连接复用本地连接
			m_HSConnect.Copy(&m_Connect);
			m_WAConnect.Copy(&m_Connect);
			m_WSConnect.Copy(&m_Connect);
		}

		m_bIsStart = TRUE;								// 创建/启动消息接收线程
		DWORD dwThreadId;
		if (!CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)&RecvProc,(LPVOID)this,0, &dwThreadId)){
			m_bIsStart = FALSE;
		}
		
		return m_bIsStart;
	};
	BOOL Stop(void){
		m_bIsStart = FALSE;
		return TRUE;
	};
	BOOL IsRun(void){
		return m_bIsStart;
	};

public:			
	void ProcessMessage(const TS_MESSAGE& msg, WPARAM wParam, LPARAM lParam, BOOL isremote ){	 // wParam 送往对象的标识
		CAbsConnection* pc = NULL;

		switch(wParam)
		{
		case CS_SERVER:
			pc = &m_CSConnect;
			break;
		case HS_SERVER:
			pc = &m_HSConnect;
			break;
		case WA_SERVER:
			pc = &m_WAConnect;
			break;
		case WS_SERVER:
			pc = &m_WSConnect;
			break;
		case TS_FROM_LOCAL:
			pc = NULL;
			break;
		}

		if (pc){
			LPTS_MESSAGE_HEAD head = (LPTS_MESSAGE_HEAD)&msg;
			pc->Send(msg.Body, head->size);						// 没有建立子线程，直接将本地消息发送给对应的地方
		}
	};
	void SetServerAddr(DWORD s_code, char* ip, WORD port){		// 设定消息将要发送出去的外部服务器地址
		struct sockaddr_in addr;
		MakeIPv4Addr(addr, ip, port);

		switch(s_code)
		{
		case CS_SERVER:
			m_CSConnect.SetPeer(addr);							// 设置配置服务器地址
			break;
		case HS_SERVER:
			m_HSConnect.SetPeer(addr);							// 设置心跳服务器地址
			break;
		case WA_SERVER:
			m_WAConnect.SetPeer(addr);							// 设置工作代理服务器地址
			break;
		case WS_SERVER:
			m_WSConnect.SetPeer(addr);							// 设置工作服务器地址
			break;	
		}
	};
	void SetServerAddr(DWORD s_code, struct sockaddr_in addr){	// 设定消息将要发送出去的外部服务器地址
		switch(s_code)
		{
		case CS_SERVER:
			m_CSConnect.SetPeer(addr);
			break;
		case HS_SERVER:
			m_HSConnect.SetPeer(addr);
			break;
		case WA_SERVER:
			m_WAConnect.SetPeer(addr);
			break;
		case WS_SERVER:
			m_WSConnect.SetPeer(addr);
			break;	
		}
	};

public:			// 对内发送消息的功能
	CAbsConnection* GetConnection(void){
		return &m_Connect;
	};
	static DWORD RecvProc(LPVOID lpParam){							// 消息的接受过程
		CClientNet* p_Net = (CClientNet*) lpParam;
		CAbsConnection* p_Connect = p_Net->GetConnection();	
		if (p_Connect == NULL){										// 链接未创建
			return 0;
		}
		else{
			if (!p_Connect->IsValidSocket()){						// 链接中的Socket未被有效创建
				return 0;
			}
		}
		
		ULONG m_nSize = sizeof(TS_MESSAGE);
		unsigned int m_nRecvSize = 0;
		TS_MESSAGE msg;
		memset(&msg, 0, m_nSize);
		
		while(p_Net->IsRun()){
			m_nRecvSize = p_Connect->Recv(msg.Body, m_nSize);
			
			if (m_nRecvSize>0 && m_nRecvSize<=m_nSize){				// 通过网络接受消息，长度大于消息长度的包一律丢弃
				p_Net->SendMessage(NULL, msg, 0, 0, TRUE);			// 接收到的消息都是来自“远端（Remote）”的, 分发给被注册的消息接受者
			}
			else{
				Sleep(1);
			}
		}

		return 1;
	};

private:
	void MakeIPv4Addr(struct sockaddr_in& addr, char* ip, WORD port){
		addr.sin_addr.s_addr = inet_addr(ip);
		addr.sin_port = htons(port);
		addr.sin_family = AF_INET;
	};
};
