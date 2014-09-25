
#include "CAbsStrategy.h"
#include "../DataUnit/CBlock.h"

CAbsStrategy::CAbsStrategy() {
}

CAbsStrategy::~CAbsStrategy() {
	resultList.clear();
}

int CAbsStrategy::getStrategyResult(set<CPackage*>& out) {
	out.insert(resultList.begin(), resultList.end());
	int size = resultList.size();
	resultList.clear();
	return size;
}