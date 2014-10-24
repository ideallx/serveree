/*
 * Server.cpp
 *
 *  Created on: Dec 12, 2012
 *      Author: root
 */

#include "CAbsServer.h"
#include "../../Stdafx.h"
#include "../Connections/CHubConnection.h"
#include "../OSInedependent/others.h"

CAbsServer::CAbsServer(void) : 
	pConnect(NULL),
	Port(0),
	isStarted(FALSE) {
	iop_lock_init(&lockStart);

	turnOff();
}

CAbsServer::~CAbsServer(void) {
    turnOff();
	iop_lock_destroy(&lockStart);
}

CAbsConnection* CAbsServer::getConnection(void) {
	return pConnect;
}

sockaddr_in* CAbsServer::getServerAddr(void) {
	if (NULL == pConnect) {
		return NULL;
	} else {
		return pConnect->getSocket()->getLocalAddr();
	}
}

bool CAbsServer::isRunning() {
	iop_lock(&lockStart);
    bool ret = isStarted;
	iop_unlock(&lockStart);
    return ret;
}

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
    cout << "SendProc exit" << endl;
	return 0;
}

void* RecvProc(LPVOID lpParam) {
	CAbsServer* pServer = (CAbsServer*) lpParam;
	if (!pServer) {
		return 0;
	}
	pServer->recvProc();
    cout << "RecvProc exit" << endl;
	return 0;
}

void* MsgProc(LPVOID lpParam) {
	pthread_detach(pthread_self());
	CAbsServer* pServer = (CAbsServer*) lpParam;
	if (NULL == pServer) {
		return 0;
	}
	pServer->msgProc();
    cout << "MsgProc exit" << endl;
	return 0;
}






