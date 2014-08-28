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
	
	// 接收队列
	// sem_t semMsg;
	HANDLE semMsg;

	CBlockManager* bm;
	bool needCacheSend;		// 是否需要将send的内容缓存下来
	TSQueue<ts_msg>* msgQueue;
	
	TS_UINT64 selfUid;

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

	// 获取BlockManager的文件地址
	string getFilePath();

	// 将某个用户的包全部保存进文件中，并删除之
	void saveUserBlock(TS_UINT64 uid);

	// 打开或者关闭send时缓存机制
	inline void switchSendCache(bool on = true) { needCacheSend = on; }
	
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

	friend int testRecv();

	set<TS_UINT64> missed;
};


#endif