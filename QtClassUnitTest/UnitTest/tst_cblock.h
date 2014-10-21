#ifndef TST_CBLOCK_H
#define TST_CBLOCK_H

#include <QObject>
#include "../QtClassClient/Reliable/DataUnit/CBlock.h"

class tst_CBlock : public QObject
{
    Q_OBJECT
public:
    tst_CBlock();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();

    void testAddMsg1();
    void testReadMsg();
    void testScanMissing();

    void init();
    void cleanup();

private:
    CBlock* test;
    ts_msg* msg;
};

#endif // TST_CBLOCK_H
