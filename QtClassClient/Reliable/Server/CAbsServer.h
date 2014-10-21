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

#include <pthread.h>
#include <semaphore.h>

#include "../Connections/CConnection.h"
#include "../DataStructure/TSQueue.h"
#include "../../Stdafx.h"
#include "../DataUnit/CMessage.h"


//#include "OSindependent\others.h"

using namespace std;

class  CAbsServer //abstract
{
protected:
	CAbsConnection* pConnect;
	unsigned short Port;
	bool isStarted;

	sem_t sem_start;
	sem_t sem_free;
	sem_t sem_count;

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
		sem_wait((sem_t*) &sem_start);
		isStarted = TRUE;
		sem_post((sem_t*) &sem_start);
	}

	void turnOff() {
		sem_wait((sem_t*) &sem_start);
		isStarted = FALSE;
		sem_post((sem_t*) &sem_start);
	}
};


void* RecvProc(LPVOID lpParam);
void* SendProc(LPVOID lpParam);
void* MsgProc(LPVOID lpParam);

#endif /* SERVER_H_ */
