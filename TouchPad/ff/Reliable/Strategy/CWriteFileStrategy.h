#ifndef _STRATEGY_CWRITEFILESTRATEGY_H_
#define _STRATEGY_CWRITEFILESTRATEGY_H_

#include "CAbsStrategy.h"

class CPackage;

class CWriteFileStrategy : public CAbsStrategy {

public:
	CWriteFileStrategy();
	~CWriteFileStrategy();

	// 直接加入resultsList
	bool onMsgAddStrategy(CPackage* pack);

	// scan时找到一个已满的包
	bool onMsgScanStrategy(CPackage* pack);
};

#endif