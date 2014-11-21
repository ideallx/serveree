#ifndef _STRATEGY_CDESTROYSTRATEGY_H_
#define _STRATEGY_CDESTROYSTRATEGY_H_

#include <map>
#include "CAbsStrategy.h"

class CPackage;


class CDestroyStrategy : public CAbsStrategy {
private:
	map<CPackage*, int> blockHP;

	static const int initialHP = 2000;

public:
	CDestroyStrategy();
	~CDestroyStrategy();

	// 将一个新的package加入到map中
	bool onMsgAddStrategy(CPackage* pack);

	// scan时扫描到一个已满的包，返回true，销毁该CPackage
	bool onMsgScanStrategy(CPackage* pack);
};

#endif