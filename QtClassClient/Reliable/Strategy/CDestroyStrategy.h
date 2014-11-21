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

	// ��һ���µ�package���뵽map��
	bool onMsgAddStrategy(CPackage* pack);

	// scanʱɨ�赽һ�������İ�������true�����ٸ�CPackage
	bool onMsgScanStrategy(CPackage* pack);
};

#endif