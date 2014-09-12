#ifndef _CONNECTION_CRELIABLECONNECTION_H_
#define _CONNECTION_CRELIABLECONNECTION_H_

#include <pthread.h>
#include <iop_thread.h>

#include "CHubConnection.h"
#include "../DataUnit/CBlockManager.h"
#include "../DataStructure/TSQueue.h"


/**
 *  可靠UDP，内含：
 *		1:	BlockManager 管理所有发出接收的文件
 *		2:	三个线程
 *			2.1:scan线程，扫描丢包，扫描需要保存的包
 *			2.2:save线程，scan时扫到需要保存的包，则交给save线程的队列，由save线程进行存文件操作
 *			2.3:msgin线程，有收到消息后就交给msgIn线程，并由msgIn来根据msg的类型选择进行保存或者重发操作
 *		3:	两个队列，都使用信号量进行保护
 *			3.1:msgQueue，收到的msg
 *			3.2:saveQueue，需要保存的package队列
 *
 *	收msg过程：
 *		收到msg，加入msgQueue，若是正常msg则返回上层msg长度，
 *							  若是异常则返回-1
 *		msgin线程读取到msg，若是正常msg则保存到blockmanager
 *						   若是异常则进行重发处理
 *
 *  发送过程：
 *		发送给多人的，使用send()，会遍历群发
 *		发送给单人使用send2peer()，会根据报文的UID，选择peer发送
 *		要向单人发送多个包，使用findpeer()->send
 *		客户端发送时，会保存副本。
 *
 *	扫描过程：
 *		打开端口后，开启scan线程
 *		每过特定时间（现在是100ms)进行一次判断，判断2项
 *			若是缺了某几个包，则请求重发
 *			若是获取到了某几个需要保存的包，则加入saveQueue，等待保存线程进行保存
 *
 *	保存过程：
 *		打开端口后，开启save线程
 *		使用信号量保护，saveQueue中如果有package加入，则进行保存
 *
 *
 *	其他:
 *		1.丢包率: 每miss一次 totalMiss++， 每收到一条 totalMsgs++
 *				 丢包率 = totalMiss / totalMsgs * 100。由于可能重复miss，所以丢包率可能过100
 *		2.createdBlock: 由于每个block的第一次创建文件需要用create模式，所以这里记录是否是第一次存文件
 *		3.selfUid: 自身UID，同时又能判断是否是server
 *		4.fileNamePrefix:本次保存的文件名前缀，一般为classid_time
 */

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
	TSQueue<pair<TS_UINT64, CPackage*> > saveQueue;	// 这里传指针应该没问题吧。

	TS_UINT64 selfUid;				// 自身的UID
	set<TS_UINT64> missed;			// 测试用client丢包数据

	set<TS_UINT64> createdBlock;	// 记录所有create过的block

	int totalMsgs;					// 总共收到的包数
	int totalMiss;					// 总共丢掉的包数

	string fileNamePrefix;			// 保存的文件名的前缀

	HANDLE needScan;				// 来了新的msg，需要重新scan

	bool resendWhenAsk;				// 是否一收到重发请求就重发（重发率过高时，设为false抑制重发）

public:
	bool isRunning;					// 是否运行，从create开始运行

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

	// 设置文件名前缀 fprefix_uid.zip/packageNum
	void setFilePrefix(string fprefix);

	// 获取丢包率（千分比 超过1000则可能是反复丢包）
	inline int getMissingRate() { return 1000 * totalMiss / totalMsgs; }

	// 所有包全部重发一遍
	int resendAll(TS_UINT64 toUID);

	// 重发某个用户的部分包
	int resendPart(TS_UINT64 toUID, TS_UINT64 needUID, 
					TS_UINT64 fromSeq, TS_UINT64 toSeq);

	// 设置正常或者抑制重发
	inline void setResendWhenAsk(bool set) { resendWhenAsk = set; }

	// 关闭reliable
	inline void stop() { isRunning = false; }

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

	// 收到数据后的处理以及转发等过程
	void receive(ts_msg& msg);
	
private:
	// 定时扫描失踪包裹。
	friend void* ScanProc(LPVOID lpParam);

	// 消息到达的处理过程
	friend void* MsgInProc(LPVOID lpParam);

	// 消息到达的处理过程
	friend void* SaveProc(LPVOID lpParam);
};


#endif