#ifndef _SERVER_DWSCLIENT_H_
#define _SERVER_DWSCLIENT_H_

#include <set>
#include <map>

#include <semaphore.h>

#include "CServer.h"
#include "../Connections/CHubConnection.h"
#include "../DataUnit/CBlockManager.h"
#include "../DataUnit/UserBase.h"
#include "../Connections/CReliableConnection.h"


class DWSClient : public CServer {
private:
	TS_UINT64 _seq;				// ��ˮ�ſ�
	UserBase* ub;				// �����û�����Ϣ
	CReliableConnection *conn;	// pConnect��dynamic cast�����
	CPeerConnection* agent;		// ����pConnect��socket����������agent serverͨ��
	DWORD timeDiff;				// �������˺Ϳͻ��˵�ʱ���

public:
	DWSClient();
	virtual ~DWSClient();

	bool Start(unsigned short port); 

	// ģ��ͻ��� �����������
	bool generateData();				
	
	DWORD MsgHandler(TS_PEER_MESSAGE& pmsg);

	// �����û�
	void setUser(UserBase& ubin);		

	// ��������
	void sendHeartBeat();

public:
	void sendProc();
	void recvProc();
	void msgProc();
	
	// ����������
	friend void* HBProc(LPVOID lpParam);

	// ���ɿͻ������ݹ���
	friend void* GenProc(LPVOID lpParam);
	
private:
	bool enterClass(ts_msg& msg);

	bool leaveClass(ts_msg& msg);

};

#endif /* CWSSERVER_H_ */
