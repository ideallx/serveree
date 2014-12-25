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

CAbsServer::CAbsServer(void)
	: pConnect(NULL)
	, Port(0)
	, isStarted(false)
	, p_InMsgQueue(new TSQueue<TS_PEER_MESSAGE>)
	, p_OutMsgQueue(new TSQueue<TS_PEER_MESSAGE>)
	, data_in(CreateSemaphore(NULL, 0, 102400, NULL))
	, data_out(CreateSemaphore(NULL, 0, 102400, NULL))  {
}

CAbsServer::~CAbsServer(void) {
    isStarted = false;
	DESTROY(p_InMsgQueue);
	DESTROY(p_OutMsgQueue);
	CloseHandle(data_in);
	CloseHandle(data_out);
	DESTROY(pConnect);
}

sockaddr_in* CAbsServer::getServerAddr(void) {
	if (NULL == pConnect) {
		return NULL;
	} else {
		return &pConnect->getSocket()->getLocalAddr();
	}
}

thread_ret_type thread_func_call SendProc(LPVOID lpParam) {
    iop_thread_detach_self();
    CAbsServer* pServer = reinterpret_cast<CAbsServer*> (lpParam);
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
    CAbsServer* pServer = reinterpret_cast<CAbsServer*> (lpParam);
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
    CAbsServer* pServer = reinterpret_cast<CAbsServer*> (lpParam);
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






