/*
 * Server.cpp
 *
 *  Created on: Dec 12, 2012
 *      Author: root
 */

#include "CAbsServer.h"
#include "../Stdafx.h"
#include "../Connections/CHubConnection.h"
#include "../OSInedependent/others.h"

CAbsServer::CAbsServer(void) : 
	pConnect(NULL),
	Port(0),
	isStarted(FALSE) {
	sem_init((sem_t*) &sem_free, 0, 1);
	sem_init((sem_t*) &sem_start, 0, 1);
	sem_init((sem_t*) &sem_count, 0, 1);

	turnOff();
}

CAbsServer::~CAbsServer(void) {
	sem_destroy((sem_t*) &sem_count);
	sem_destroy((sem_t*) &sem_start);
	sem_destroy((sem_t*) &sem_free);
}

CAbsConnection* CAbsServer::getConnection(void) {
	return pConnect;
};

sockaddr_in* CAbsServer::getServerAddr(void) {
	if (NULL == pConnect) {
		return NULL;
	} else {
		return pConnect->getSocket()->getLocalAddr();
	}
}

bool CAbsServer::isRunning(){
	bool ret;
	//sem_wait((sem_t*) &sem_start);
	ret = isStarted;
	//sem_post((sem_t*) &sem_start);
	return ret;
};

unsigned short CAbsServer::getPort(void) {
	return Port;
}

void* SendProc(LPVOID lpParam) {
	pthread_detach(pthread_self());
	CAbsServer* pServer = (CAbsServer*) lpParam;
	if (!pServer) {
		return 0;
	}
	pServer->sendProc();
	return 0;
}

void* RecvProc(LPVOID lpParam) {
	pthread_detach(pthread_self());
	CAbsServer* pServer = (CAbsServer*) lpParam;
	if (!pServer) {
		return 0;
	}
	pServer->recvProc();
	return 0;
}

void* MsgProc(LPVOID lpParam) {
	pthread_detach(pthread_self());
	CAbsServer* pServer = (CAbsServer*) lpParam;
	if (NULL == pServer) {
		return 0;
	}
	pServer->msgProc();
	return 0;
}






