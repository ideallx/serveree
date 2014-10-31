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

	iop_lock_t lockStart;

public:
	CAbsServer();
	virtual ~CAbsServer(void);

public:
	virtual bool Initialize(void) = 0;
	virtual bool Uninitialize(void) = 0;
	virtual bool Start(unsigned short port) = 0;
	virtual bool Stop(void) = 0;
	virtual DWORD MsgHandler(TS_PEER_MESSAGE& pmsg) = 0;		// 消息处理

public:
	virtual void ReadIn(TS_PEER_MESSAGE& pmsg) = 0;
	virtual void WriteIn(const TS_PEER_MESSAGE& pmsg) = 0;
	virtual void ReadOut(TS_PEER_MESSAGE& pmsg) = 0;
	virtual void WriteOut(const TS_PEER_MESSAGE& pmsg) = 0;

	virtual void sendProc() = 0;
	virtual void recvProc() = 0;
	virtual void msgProc() = 0;

public:
	bool isRunning();
	CAbsConnection* getConnection(void);
	sockaddr_in* getServerAddr(void);
	unsigned short getPort(void);
	
	void turnOn() {
		iop_lock(&lockStart);
		isStarted = TRUE;
		iop_unlock(&lockStart);
	}

	void turnOff() {
		iop_lock(&lockStart);
		isStarted = FALSE;
		iop_unlock(&lockStart);
	}
};


thread_ret_type thread_func_call RecvProc(LPVOID lpParam);
thread_ret_type thread_func_call SendProc(LPVOID lpParam);
thread_ret_type thread_func_call MsgProc(LPVOID lpParam);

#endif /* SERVER_H_ */
