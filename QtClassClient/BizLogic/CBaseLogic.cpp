#include "CBaseLogic.h"

CBaseLogic::CBaseLogic(CMsgObject* parent) :
	CMsgObject(parent) {


}

CBaseLogic::~CBaseLogic() {


}

bool CBaseLogic::procMsg(const ts_msg& msg, bool isRemote) {
    return false;
}
