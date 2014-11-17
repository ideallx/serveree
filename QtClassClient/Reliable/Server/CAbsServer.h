/*
 * Server.h
 *
 *  Created on: Dec 12, 2012
 *      Author: root
 */
#pragma once

#ifndef _SERVER_CABSSERVER_H_
#define _SERVER_CABSSERVER_H_

#include <iostream>

#include <vector>
#include <iop_thread.h>


#include "../DataUnit/CMessage.h"
#include "../Connections/CConnection.h"
#include "../DataStructure/TSQueue.h"

using namespace std;

class  CAbsServer //abstract
{
protected:
	CAbsConnection* pConnect;
	unsigned short Port;
	bool isStarted;
	TSQueue<TS_PEER_MESSAGE>* p_InMsgQueue;				// 接收队列 in Queue
	TSQueue<TS_PEER_MESSAGE>* p_OutMsgQueue;			// 发送队列 out Queue
	HANDLE data_in;
	HANDLE data_out;

public:
	CAbsServer();
	virtual ~CAbsServer(void);

public:
	virtual bool Start(unsigned short port) = 0;
	virtual DWORD MsgHandler(TS_PEER_MESSAGE& pmsg) = 0;		// 消息处理

public:
	inline void ReadIn(TS_PEER_MESSAGE& pmsg) {
		WaitForSingleObject(data_in, INFINITE);
		p_InMsgQueue->deQueue(pmsg);
	}
	inline void WriteIn(const TS_PEER_MESSAGE& pmsg) {
		p_InMsgQueue->enQueue(pmsg);
		ReleaseSemaphore(data_in, 1, NULL);
	}
	inline void ReadOut(TS_PEER_MESSAGE& pmsg) {
		WaitForSingleObject(data_out, INFINITE);
		p_OutMsgQueue->deQueue(pmsg);
	}
	inline void WriteOut(const TS_PEER_MESSAGE& pmsg) {
		p_OutMsgQueue->enQueue(pmsg);
		ReleaseSemaphore(data_out, 1, NULL);
	}

    inline void turnOn() { isStarted = true; }
    inline void turnOff() { isStarted = false; }

	virtual void sendProc() = 0;
	virtual void recvProc() = 0;
	virtual void msgProc() = 0;



public:
	inline bool isRunning() { return isStarted; }

	inline CAbsConnection* getConnection(void) { return pConnect; }
	inline unsigned short getPort(void) { return Port; }
	
	sockaddr_in* getServerAddr(void);
};


thread_ret_type thread_func_call RecvProc(LPVOID lpParam);
thread_ret_type thread_func_call SendProc(LPVOID lpParam);
thread_ret_type thread_func_call MsgProc(LPVOID lpParam);

#endif /* SERVER_H_ */
