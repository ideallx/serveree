#ifndef _SERVER_DWSCLIENT_H_
#define _SERVER_DWSCLIENT_H_

#include <set>
#include <map>

#include <semaphore.h>

#include "CServer.h"
#include "../Connections/CHubConnection.h"
#include "../DataUnit/CBlockManager.h"
#include "../DataUnit/UserBase.h"
#include "../Connections/CReliableConnection.h"


class DWSClient : public CServer {
private:
	TS_UINT64 _seq;				// 流水号咯
	UserBase* ub;				// 本地用户的信息
	CReliableConnection *conn;	// pConnect的dynamic cast后产物
	CPeerConnection* agent;		// 复用pConnect的socket，用他来和agent server通信
	DWORD timeDiff;				// 服务器端和客户端的时间差

public:
	DWSClient();
	virtual ~DWSClient();

	bool Start(unsigned short port); 

	// 模拟客户端 生成随机数据
	bool generateData();				
	
	DWORD MsgHandler(TS_PEER_MESSAGE& pmsg);

	// 设置用户
	void setUser(UserBase& ubin);		

	// 心跳过程
	void sendHeartBeat();

public:
	void sendProc();
	void recvProc();
	void msgProc();
	
	// 心跳包过程
	friend void* HBProc(LPVOID lpParam);

	// 生成客户端数据过程
	friend void* GenProc(LPVOID lpParam);
	
private:
	bool enterClass(ts_msg& msg);

	bool leaveClass(ts_msg& msg);

};

#endif /* CWSSERVER_H_ */
