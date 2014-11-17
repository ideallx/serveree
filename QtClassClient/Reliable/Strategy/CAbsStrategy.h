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
	// ��ĳ��CPackageʹ�ò���
	virtual bool onMsgAddStrategy(CPackage* pack) = 0;

	// scanʱ����
	virtual bool onMsgScanStrategy(CPackage* pack) = 0;

	// ��ȡ���
	virtual int getStrategyResult(set<CPackage*>& out);
};

#endif
