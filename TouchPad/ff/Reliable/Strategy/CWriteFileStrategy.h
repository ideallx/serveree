#ifndef _STRATEGY_CWRITEFILESTRATEGY_H_
#define _STRATEGY_CWRITEFILESTRATEGY_H_

#include "CAbsStrategy.h"

class CPackage;

class CWriteFileStrategy : public CAbsStrategy {

public:
	CWriteFileStrategy();
	~CWriteFileStrategy();

	// ֱ�Ӽ���resultsList
	bool onMsgAddStrategy(CPackage* pack);

	// scanʱ�ҵ�һ�������İ�
	bool onMsgScanStrategy(CPackage* pack);
};

#endif