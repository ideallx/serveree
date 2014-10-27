#include "UnitTest/tst_CPackage.h"
#include "UnitTest/tst_cblock.h"
#include "UnitTest/tst_cblockmanager.h"
#include "UnitTest/tst_reliable.h"
#include "UnitTest/tst_cagentserver.h"
#include "UnitTest/tst_cserver.h"

int main(int argc, char *argv[])
{
    WSADATA wsadata;
    WSAStartup(MAKEWORD(2, 2),&wsadata);

    QApplication app(argc, argv);
    app.setAttribute(Qt::AA_Use96Dpi, true);
    QTEST_DISABLE_KEYPAD_NAVIGATION

    tst_CPackage package;
    tst_CBlock block;
    tst_CBlockManager blockmanager;
    tst_Reliable reliable;
    tst_CAgentServer agentserver;
    tst_CServer server;

    int calc = 0;
    calc += QTest::qExec(&package, argc, argv);
    calc += QTest::qExec(&block, argc, argv);
    calc += QTest::qExec(&blockmanager, argc, argv);
    calc += QTest::qExec(&reliable, argc, argv);
    calc += QTest::qExec(&agentserver, argc, argv);
    calc += QTest::qExec(&server, argc, argv);

    cout << "total error: " << calc << endl;
    return calc;
}
