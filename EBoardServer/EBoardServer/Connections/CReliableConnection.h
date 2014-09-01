#ifndef _CONNECTION_CRELIABLECONNECTION_H_
#define _CONNECTION_CRELIABLECONNECTION_H_

#include <pthread.h>
#include <iop_thread.h>

#include "CHubConnection.h"
#include "../DataUnit/CBlockManager.h"
#include "../DataStructure/TSQueue.h"


class CReliableConnection : public CHubConnection {
protected:
	pthread_t msgScan;	
	pthread_t msgIn;
	pthread_t msgSave;
	
	// 接收队列
	HANDLE semMsg;					// 消息处理信号量
	HANDLE semSave;					// 存文件信号量

	CBlockManager* bm;

	TSQueue<ts_msg>* msgQueue;
	TSQueue<pair<TS_UINT64, CPackage*> > saveQueue;	// bao这里传指针应该没问题吧。

	TS_UINT64 selfUid;				// 自身的UID
	set<TS_UINT64> missed;			// 测试用client丢包数据

	set<TS_UINT64> createdBlock;	// 记录所有create过的block

public:

	CReliableConnection();
	virtual ~CReliableConnection();

	// 创建socket，并开启scan线程
	bool create(unsigned short localport = 0);

	// 不停收包，异常包自己处理，正常包交给上层，返回消息长度
	int recv(char* buf, ULONG& len);

	// 发送时保存副本
	int send(const char* buf, ULONG len);

	// 扫描一遍整个block发现有丢失的就发送重发请求
	void scanProcess();

	// 存文件线程，维护一个存文件队列
	void saveProcess();

	// 获取BlockManager的文件地址
	string getFilePath();

	// 将某个用户的包全部保存进文件中，并删除之
	void saveUserBlock(TS_UINT64 uid);

	// 用UID来区分Server还是Client端，另外重传请求时需要提供自己的UID
	void setUID(TS_UINT64 in) { selfUid = in; }

private:
	// 将需要发送的消息添加至消息队列
	int send2Peer(ts_msg& msg);

	// 将需要发送的消息添加至消息队列，发送给另一个uid对应的地址
	int send2Peer(ts_msg& msg, TS_UINT64 uid);

	// 自己接收缺失，问对端要，返回发出去了几个包  回头改函数名
	int requestForResend(TS_UINT64 uid, set<TS_UINT64> pids);

	// 自己发送缺失，处理对端请求，返回发出去了几个包
	int resend(ts_msg& requestMsg);

	// 数据报文有效性检查
	bool validityCheck(ts_msg& msg);
	
private:
	// 定时扫描失踪包裹。
	friend void* ScanProc(LPVOID lpParam);

	// 消息到达的处理过程
	friend void* MsgInProc(LPVOID lpParam);

	// 消息到达的处理过程
	friend void* SaveProc(LPVOID lpParam);

	friend int testRecv();
};


#endif