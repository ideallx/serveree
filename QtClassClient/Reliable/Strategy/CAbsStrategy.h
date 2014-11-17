#ifndef _STRATEGY_CABSSTRATEGY_H_
#define _STRATEGY_CABSSTRATEGY_H_

class CBlock;
class CPackage;

#include "../DataUnit/CMessage.h"
#include <set>

class CAbsStrategy {
protected:
	set<CPackage*> resultList;

public:
	CAbsStrategy();
	~CAbsStrategy();

public:
	// 对某个CPackage使用策略
	virtual bool onMsgAddStrategy(CPackage* pack) = 0;

	// scan时触发
	virtual bool onMsgScanStrategy(CPackage* pack) = 0;

	// 获取结果
	virtual int getStrategyResult(set<CPackage*>& out);
};

#endif
