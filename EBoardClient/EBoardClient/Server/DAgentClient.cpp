#include <iostream>
#include <string>

#include "DAgentClient.h"

#pragma pack(4)

using namespace std;

DAgentClient::DAgentClient() :
	ub (NULL) {
}

DAgentClient::~DAgentClient() {
	DESTROY(ub);
}

bool DAgentClient::isClassExist(TS_UINT64 classid) {
	return (workClients.count(classid) > 0) && 
		(workClients[classid] != NULL);
}

DWORD DAgentClient::MsgHandler(TS_PEER_MESSAGE& inputMsg) {			// 创建新的客户端WSClient
	enum PackageType type = getType(inputMsg.msg);
	DOWN_AGENTSERVICE* in = (DOWN_AGENTSERVICE*) &inputMsg.msg;
	if (ENTERCLASS == in->head.type) {
		if (in->result == Success) {
			DWSClient *dws = new DWSClient(ntohs(in->addr.sin_port), 2);
			dws->Start(ntohs(in->addr.sin_port));
		}
	}
	return 0;
}

bool DAgentClient::enterClass(ts_msg& msg) {			// 拼接进入班级的报文
	if (NULL == ub)
		return false;

	TS_UINT64 uid = ub->_uid;
	UP_AGENTSERVICE* upcmd = (UP_AGENTSERVICE*) &msg;
	upcmd->head.type = ENTERCLASS;
	upcmd->head.UID = uid;
	upcmd->head.reserved = ub->_reserved;
	upcmd->classid = ub->_classid;
	upcmd->role = static_cast<enum RoleOfClass> (ub->_role);
	memcpy(upcmd->username, ub->_username, 20);
	memcpy(upcmd->password, ub->_password, 20);
	return true;
}

void DAgentClient::sendProc() {
	TS_PEER_MESSAGE pmsg;
	memset(&pmsg, 0, sizeof(TS_PEER_MESSAGE));

	CAbsConnection* pPeerConn = new CPeerConnection();
	if (!pPeerConn->copy(getConnection())) {
		return;
	}

	enterClass(pmsg.msg);								// Agent开启，直接就进班级
	if (pPeerConn->send(pmsg.msg.Body, sizeof(ts_msg)) < 0)
		cout << "send error in sendproc" << endl;
}

void DAgentClient::setUser(UserBase& ubin) {			// 设置本机信息
	if (NULL == ub) {
		ub = new UserBase();
	}
	memcpy(ub, &ubin, sizeof(UserBase));
}

bool DAgentClient::Start(unsigned short port) {
	// CConnection or Queue
	if (pConnect == NULL 
		|| p_InMsgQueue == NULL 
		|| p_OutMsgQueue == NULL 
		|| isStarted)
		return FALSE;

	Port = port;

	if (!pConnect->create(0)) {
		return FALSE;
	}

	
	SOCKADDR_IN addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr("192.168.1.202");
	addr.sin_port = htons(port);
	pConnect->setPeer(addr);

	turnOn();
	if (!Initialize ())
		return FALSE;

	for (unsigned int i = 0; i < recvthread_num; i++) {
		int rc = pthread_create(&pthread_recv[i], NULL, RecvProc, (void*) this);
		if (0 == rc) {
			iop_usleep(10);
			cout << "Recv Thread start successfully " << endl;
		} else {
			turnOff();
		}
	}


	for (unsigned int i = 0; i < sendthread_num; i++) {
		int rc = pthread_create(&pthread_send[i], NULL, SendProc, (void*) this);
		if (0 == rc) {
			iop_usleep(10);
			cout << "Send Thread start successfully " << endl;
		} else {
			turnOff();
		}
	}

	for (unsigned int i = 0; i < msgthread_num; i++) {
		int rc = pthread_create(&pthread_msg[i], NULL, MsgProc, (void*) this);
		if (rc == 0) {
			iop_usleep(10);
			cout << "Msg Thread start successfully" << endl;
		} else {
			turnOff();
		}
	}

	return isRunning();
}
