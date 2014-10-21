#include "UnitTest/tst_CPackage.h"
#include "UnitTest/tst_cblock.h"
#include "UnitTest/tst_cblockmanager.h"
#include "UnitTest/tst_reliable.h"
#include "UnitTest/tst_cagentserver.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setAttribute(Qt::AA_Use96Dpi, true);
    QTEST_DISABLE_KEYPAD_NAVIGATION

    tst_CPackage tc;
    tst_CBlock tcb;
    tst_CBlockManager tcbm;
    tst_Reliable tcr;
    tst_CAgentServer tcas;

    int calc = 0;
//    calc += QTest::qExec(&tc, argc, argv);
//    calc += QTest::qExec(&tcb, argc, argv);
//    calc += QTest::qExec(&tcbm, argc, argv);
//    calc += QTest::qExec(&tcr, argc, argv);
    calc += QTest::qExec(&tcas, argc, argv);

    return calc;
}
