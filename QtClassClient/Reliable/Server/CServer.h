#ifndef _SERVER_CSERVER_H_
#define _SERVER_CSERVER_H_


#include "CAbsServer.h"

class  CServer : public CAbsServer
{

private:
	ULONG MsgLen;

protected:
	unsigned int recvthread_num;
	unsigned int sendthread_num;
	unsigned int msgthread_num;

    iop_thread_t* pthread_recv;
    iop_thread_t* pthread_send;
    iop_thread_t* pthread_msg;
	
	TSQueue<TS_PEER_MESSAGE>* p_InMsgQueue;				// 接收队列 in Queue
	TSQueue<TS_PEER_MESSAGE>* p_OutMsgQueue;			// 发送队列 out Queue
	
	HANDLE data_in;
	HANDLE data_out;

public:
	CServer();
	virtual ~CServer(void);

public:
	void ReadIn(TS_PEER_MESSAGE& pmsg);
	void WriteIn(const TS_PEER_MESSAGE& pmsg);
	void ReadOut(TS_PEER_MESSAGE& pmsg);
	void WriteOut(const TS_PEER_MESSAGE& pmsg);

	void sendProc();
	void recvProc();
	void msgProc();

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

    friend thread_ret_type thread_func_call RecvProc(LPVOID lpParam);		// 缓存过程
    friend thread_ret_type thread_func_call SendProc(LPVOID lpParam);		// 缓存过程
    friend thread_ret_type thread_func_call MsgProc(LPVOID lpParam);		// ip packet -> message, 然后处理
};



#endif
