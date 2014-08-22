#ifndef _SERVER_CSERVER_H_
#define _SERVER_CSERVER_H_


#include "CAbsServer.h"

class  CServer : public CAbsServer
{
	friend void* RecvProc(LPVOID lpParam);				// 缓存过程
	friend void* SendProc(LPVOID lpParam);				// 缓存过程
	friend void* MsgProc(LPVOID lpParam);				// ip packet -> message, 然后处理

private:
	ULONG MsgLen;

protected:
	unsigned int recvthread_num;
	unsigned int sendthread_num;
	unsigned int msgthread_num;

	pthread_t* pthread_recv;
	pthread_t* pthread_send;
	pthread_t* pthread_msg;
	
	TSQueue<TS_PEER_MESSAGE>* p_InMsgQueue;				// 接收队列 in Queue
	TSQueue<TS_PEER_MESSAGE>* p_OutMsgQueue;			// 发送队列 out Queue
	
	//sem_t data_in;										// 信号量
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