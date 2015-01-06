#include "datasingleton.h"

DataSingleton* DataSingleton::pUniqueData = NULL;

DataSingleton::DataSingleton() {
    iop_lock_init(&lockClasses);
    iop_lock_init(&lockUsers);
    iop_lock_init(&lockSingle);
}

DataSingleton* DataSingleton::getInstance() {
    if (NULL == pUniqueData) {
        pUniqueData = new DataSingleton();
    }

    return pUniqueData;
}

bool DataSingleton::addClass(TS_UINT64 classid, CLASS_INFO info) {
    if (allclasses.count(classid) > 0)
        return false;

    iop_lock(&lockClasses);
    allclasses.insert(make_pair(classid, info));
    iop_unlock(&lockClasses);

    return true;
}

bool DataSingleton::removeClass(TS_UINT64 classid) {
    if (allclasses.count(classid) > 0)
        return false;

    iop_lock(&lockClasses);
    allclasses.erase(classid);
    iop_unlock(&lockClasses);

    return true;
}

void DataSingleton::getAllClasses(map<TS_UINT64, CLASS_INFO> &allcls) {
    iop_lock(&lockClasses);
    allcls = allclasses;
    iop_unlock(&lockClasses);
}

void DataSingleton::setUser(TS_UINT64 uid, USER_INFO info) {
    iop_lock(&lockUsers);
    if (allusers.find(uid) != allusers.end()) {
        info.isWriteable = allusers[uid].isWriteable;
        allusers[uid] = info;
    } else {
        allusers.insert(make_pair(uid, info));
    }
    iop_unlock(&lockUsers);
}

void DataSingleton::setLoggedInState(TS_UINT64 uid, bool in) {
    iop_lock(&lockUsers);
    if (allusers.find(uid) != allusers.end()) {
        allusers[uid].isLoggedIn = in;
    }
    iop_unlock(&lockUsers);
}

void DataSingleton::setWriteable(TS_UINT64 uid, bool writeable) {
    iop_lock(&lockUsers);
    if (allusers.find(uid) != allusers.end()) {
        allusers[uid].isWriteable = writeable;
    }
    iop_unlock(&lockUsers);
}

WORD DataSingleton::getRole(TS_UINT64 uid) {
    if (allusers.find(uid) == allusers.end()) {
        return -1;
    }
    return allusers[uid].role;
}

//void DataSingleton::setUID(TS_UINT64 uid) {
//    iop_lock(&lockSingle);
//    selfUID = uid;
//    iop_unlock(&lockSingle);
//}

//TS_UINT64 DataSingleton::getUID() {
//    iop_lock(&lockSingle);
//    TS_UINT64 result = selfUID;
//    iop_unlock(&lockSingle);

//    return result;
//}

//void DataSingleton::setTimeDiff(TS_UINT64 td) {
//    iop_lock(&lockSingle);
//    selfUID = timeDiff;
//    iop_unlock(&lockSingle);
//}

//TS_UINT64 DataSingleton::getTimeDiff() {
//    iop_lock(&lockSingle);
//    TS_UINT64 result = timeDiff;
//    iop_unlock(&lockSingle);

//    return result;
//}

