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

public:
	CServer();
	virtual ~CServer(void);

public:
	void sendProc();
	void recvProc();
	void msgProc();

public:
	bool Start(unsigned short port = 0);
	bool Stop(void);
	DWORD MsgHandler(TS_PEER_MESSAGE& pmsg);

public:
	inline TS_UINT64 AllocateSessionID(void) { return getServerTime(); }

    friend thread_ret_type thread_func_call RecvProc(LPVOID lpParam);		// 缓存过程
    friend thread_ret_type thread_func_call SendProc(LPVOID lpParam);		// 缓存过程
    friend thread_ret_type thread_func_call MsgProc(LPVOID lpParam);		// ip packet -> message, 然后处理
};



#endif
