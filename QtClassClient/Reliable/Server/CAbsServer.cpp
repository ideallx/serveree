/*
 * Server.cpp
 *
 *  Created on: Dec 12, 2012
 *      Author: root
 */

#include <iop_thread.h>
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

thread_ret_type thread_func_call SendProc(LPVOID lpParam) {
    iop_thread_detach_self();
    CAbsServer* pServer = (CAbsServer*) lpParam;
	if (!pServer) {
        iop_thread_exit(0);
		return 0;
	}
	pServer->sendProc();
#ifdef _DEBUG_INFO_
    cout << "SendProc exit" << endl;
#endif
    iop_thread_exit(0);
	return 0;
}

thread_ret_type thread_func_call RecvProc(LPVOID lpParam) {
    iop_thread_detach_self();
    CAbsServer* pServer = (CAbsServer*) lpParam;
	if (!pServer) {
        iop_thread_exit(0);
		return 0;
	}
	pServer->recvProc();
#ifdef _DEBUG_INFO_
    cout << "RecvProc exit" << endl;
#endif
    iop_thread_exit(0);
	return 0;
}

thread_ret_type thread_func_call MsgProc(LPVOID lpParam) {
    iop_thread_detach_self();
	CAbsServer* pServer = (CAbsServer*) lpParam;
	if (NULL == pServer) {
        iop_thread_exit(0);
		return 0;
	}
	pServer->msgProc();
#ifdef _DEBUG_INFO_
    cout << "MsgProc exit" << endl;
#endif
    iop_thread_exit(0);
	return 0;
}






