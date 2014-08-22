#ifndef _SERVER_CSERVER_H_
#define _SERVER_CSERVER_H_


#include "CAbsServer.h"

class  CServer : public CAbsServer
{
	friend void* RecvProc(LPVOID lpParam);				// �������
	friend void* SendProc(LPVOID lpParam);				// �������
	friend void* MsgProc(LPVOID lpParam);				// ip packet -> message, Ȼ����

private:
	ULONG MsgLen;

protected:
	unsigned int recvthread_num;
	unsigned int sendthread_num;
	unsigned int msgthread_num;

	pthread_t* pthread_recv;
	pthread_t* pthread_send;
	pthread_t* pthread_msg;
	
	TSQueue<TS_PEER_MESSAGE>* p_InMsgQueue;				// ���ն��� in Queue
	TSQueue<TS_PEER_MESSAGE>* p_OutMsgQueue;			// ���Ͷ��� out Queue
	
	//sem_t data_in;										// �ź���
	//sem_t data_out;
	HANDLE data_in;
	HANDLE data_out;

public:
	CServer();
	virtual ~CServer(void);
	int starttime;

public:
	void ReadIn(TS_PEER_MESSAGE& pmsg);
	void WriteIn(const TS_PEER_MESSAGE& pmsg);
	void ReadOut(TS_PEER_MESSAGE& pmsg);
	void WriteOut(const TS_PEER_MESSAGE& pmsg);

	void sendProc() {};
	void recvProc() {};
	void msgProc() {};

public:
	bool Initialize(void);
	bool Uninitialize(void);
	bool Start(unsigned short port = 0);
	bool Stop(void);
	DWORD MsgHandler(TS_PEER_MESSAGE& pmsg);

private:
	bool ReadIniFile(void);

public:
	TS_UINT64 AllocateSessionID(void);
};



#endif