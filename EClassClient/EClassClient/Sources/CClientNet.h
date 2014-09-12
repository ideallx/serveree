#pragma once

#include "../stdafx.h"
#include "CMessageObject.h"
#include "../../../EBoardServer/EBoardServer/Connections/CReliableConnection.h"

// Network Communication Controller
class CClientNet : public CMessageObject
{
private:
	CReliableConnection	m_Connect;					// ��������,
	struct sockaddr_in	m_Addr;
	BOOL				m_bIsStart;					// �����̵߳Ŀ���

public:
	CClientNet(void){
		m_bIsStart	= FALSE;
	};
	virtual ~CClientNet(void){
		Stop();										// ���û��ֹͣ����ֹͣ���ݷ���
		Sleep(100);									// �ȴ����߳��˳�

		m_CSConnect.Delete();						// ��������
		m_HSConnect.Delete();
		m_WAConnect.Delete();
		m_WSConnect.Delete();

		m_Connect.Delete();								// ��Դ��ַ�����ɾ��
	};

public:				// ��������ģ��
	BOOL Start(void){
		if (m_bIsStart)									// �Ѿ�����
			return TRUE;

		if (!m_Connect.Create()){						// ������������
			return FALSE;
		}
		else{
			m_CSConnect.Copy(&m_Connect);				// ���������Ӹ��ñ�������
			m_HSConnect.Copy(&m_Connect);
			m_WAConnect.Copy(&m_Connect);
			m_WSConnect.Copy(&m_Connect);
		}

		m_bIsStart = TRUE;								// ����/������Ϣ�����߳�
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
	void ProcessMessage(const TS_MESSAGE& msg, WPARAM wParam, LPARAM lParam, BOOL isremote ){	 // wParam ��������ı�ʶ
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
			pc->Send(msg.Body, head->size);						// û�н������̣߳�ֱ�ӽ�������Ϣ���͸���Ӧ�ĵط�
		}
	};
	void SetServerAddr(DWORD s_code, char* ip, WORD port){		// �趨��Ϣ��Ҫ���ͳ�ȥ���ⲿ��������ַ
		struct sockaddr_in addr;
		MakeIPv4Addr(addr, ip, port);

		switch(s_code)
		{
		case CS_SERVER:
			m_CSConnect.SetPeer(addr);							// �������÷�������ַ
			break;
		case HS_SERVER:
			m_HSConnect.SetPeer(addr);							// ����������������ַ
			break;
		case WA_SERVER:
			m_WAConnect.SetPeer(addr);							// ���ù��������������ַ
			break;
		case WS_SERVER:
			m_WSConnect.SetPeer(addr);							// ���ù�����������ַ
			break;	
		}
	};
	void SetServerAddr(DWORD s_code, struct sockaddr_in addr){	// �趨��Ϣ��Ҫ���ͳ�ȥ���ⲿ��������ַ
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

public:			// ���ڷ�����Ϣ�Ĺ���
	CAbsConnection* GetConnection(void){
		return &m_Connect;
	};
	static DWORD RecvProc(LPVOID lpParam){							// ��Ϣ�Ľ��ܹ���
		CClientNet* p_Net = (CClientNet*) lpParam;
		CAbsConnection* p_Connect = p_Net->GetConnection();	
		if (p_Connect == NULL){										// ����δ����
			return 0;
		}
		else{
			if (!p_Connect->IsValidSocket()){						// �����е�Socketδ����Ч����
				return 0;
			}
		}
		
		ULONG m_nSize = sizeof(TS_MESSAGE);
		unsigned int m_nRecvSize = 0;
		TS_MESSAGE msg;
		memset(&msg, 0, m_nSize);
		
		while(p_Net->IsRun()){
			m_nRecvSize = p_Connect->Recv(msg.Body, m_nSize);
			
			if (m_nRecvSize>0 && m_nRecvSize<=m_nSize){				// ͨ�����������Ϣ�����ȴ�����Ϣ���ȵİ�һ�ɶ���
				p_Net->SendMessage(NULL, msg, 0, 0, TRUE);			// ���յ�����Ϣ�������ԡ�Զ�ˣ�Remote������, �ַ�����ע�����Ϣ������
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
