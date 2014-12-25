#ifndef DATASINGLETON_H
#define DATASINGLETON_H

#include <map>
#include <iop_thread.h>
#include "../Reliable/DataUnit/CMessage.h"

using namespace std;


class DataSingleton
{
private:
    DataSingleton();
    static DataSingleton *pUniqueData;

public:
    static DataSingleton* getInstance();

private:
    map<TS_UINT64, CLASS_INFO> allclasses;
    map<TS_UINT64, USER_INFO> allusers;

    TS_UINT64 selfUID;
    TS_UINT64 timeDiff;

    iop_lock_t lockClasses;
    iop_lock_t lockUsers;
    iop_lock_t lockSingle;

public:
    // 这里还是不锁了
    inline void setUID(TS_UINT64 uid) { selfUID = uid; }
    inline TS_UINT64 getUID() { return selfUID; }

    inline void setTimeDiff(TS_UINT64 td) { timeDiff = td; }
    inline TS_UINT64 getTimeDiff() { return timeDiff; }

    bool addClass(TS_UINT64 classid, CLASS_INFO info);
    bool removeClass(TS_UINT64 classid);
    void getAllClasses(map<TS_UINT64, CLASS_INFO> &allcls);

    void setUser(TS_UINT64 uid, USER_INFO info);
    void setLoggedInState(TS_UINT64 uid, bool in);
    void setWriteable(TS_UINT64 uid, bool writeable);
    inline map<TS_UINT64, USER_INFO> getAllUsers() const { return allusers; }

    inline int getRole() { return allusers[selfUID].role; }

};

#endif // DATASINGLETON_H
