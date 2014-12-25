#include "cloadlogic.h"

CLoadLogic::CLoadLogic(CMsgObject *parent):
    CBaseLogic(parent) {

}

bool CLoadLogic::procMsg(const ts_msg& msg, bool isRemote) {
    TS_MESSAGE_HEAD* hmsg = (TS_MESSAGE_HEAD*) &msg;
    if (!isRemote)
        return false;

    TS_UINT64 uid = hmsg->UID;
    if (userInfo.find(uid) == userInfo.end()) {
        CSubSeqUnit sub;
        userInfo.insert(make_pair(uid, sub));
    }
    return true;
}
