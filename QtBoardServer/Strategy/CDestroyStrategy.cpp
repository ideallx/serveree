#include "CDestroyStrategy.h"

CDestroyStrategy::CDestroyStrategy() {

}


CDestroyStrategy::~CDestroyStrategy() {
	blockHP.clear();
}

bool CDestroyStrategy::onMsgAddStrategy(CPackage* pack) {
	if (blockHP.count(pack) != 0)
		return false;

	blockHP.insert(make_pair(pack, initialHP));
	return true;
}

bool CDestroyStrategy::onMsgScanStrategy(CPackage* pack) {
	if (blockHP.count(pack) == 0)
		return false;

	int hp = --blockHP[pack];
	if (hp == 0) {
		blockHP.erase(pack);
		return true;
	}
	return false;
}