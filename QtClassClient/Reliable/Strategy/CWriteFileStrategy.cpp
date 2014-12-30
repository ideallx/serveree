#include "CWriteFileStrategy.h"
#include "../DataUnit/CPackage.h"

CWriteFileStrategy::CWriteFileStrategy() {

}

CWriteFileStrategy::~CWriteFileStrategy() {

}

bool CWriteFileStrategy::onMsgAddStrategy(CPackage* pack) {
	resultList.insert(pack);
	return true;
}

bool CWriteFileStrategy::onMsgScanStrategy(CPackage* pack) {
	if (pack->isSaved())
		return false;
	resultList.insert(pack);
	return true;
}
