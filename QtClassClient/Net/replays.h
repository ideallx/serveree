#ifndef REPLAYS_H
#define REPLAYS_H

#include <set>
#include <map>
#include <QString>

#include "../Reliable/DataUnit/CMessage.h"
#include "../Reliable/DataUnit/CBlockManager.h"

#include <QMap>

using namespace std;

class Replays
{
public:
    Replays(string className);
    virtual ~Replays();

    int test();

    /**
     * @brief getNextMsg
     * @param msg
     * @return true: has remaining replay msg, false: replay end
     *
     * sleepTime is after msg
     */
    bool getNextMsg(ts_msg& msg, int &sleepTime);

    bool getNextMsg2(ts_msg& msg, int &sleepTime);

private:
    void addPackage(CPackage* package);

private:
    CBlockManager* fakebm;
    set<TS_UINT64> blocks;
    map<TS_UINT64, ts_msg> records;
    CPackage        temp;

    QMap<TS_UINT64, ts_msg> recs;

    bool isInited;
};

#endif // REPLAYS_H
