#ifndef TST_CBLOCKMANAGER_H
#define TST_CBLOCKMANAGER_H

#include <QObject>
#include "../QtClassClient/Reliable/DataUnit/CBlockManager.h"

class tst_CBlockManager : public QObject
{
    Q_OBJECT
public:
    tst_CBlockManager();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();

    void init();
    void cleanup();

    void testRecord();
    void testRecord2();
    void testMemoryBlock();

private:
    CBlockManager* test;
    ts_msg* msg;
};

#endif // TST_CBLOCKMANAGER_H
