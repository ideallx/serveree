#include <QString>
#include <QtTest>
#include <QCoreApplication>
#include "../QtClassClient/Reliable/DataUnit/CPackage.h"

class tst_CPackage : public QObject
{
    Q_OBJECT

public:
    tst_CPackage();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();

    void testInsert1();
    void testInsert2();
    void testInsert3();
    void testQuery1();
    void testQuery2();
    void testSave();
    void testLoad();
    void testIsExist();
    void testIsFull1();
    void testIsFull2();
    void testScanAll();
    void testScanMissingPackets();
    void testScanMissingPackets2();

    void init();
    void cleanup();

private:
    CPackage* test;
    ts_msg* msg;
};
