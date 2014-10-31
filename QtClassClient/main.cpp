#include <QApplication>
#include <QObject>
#include <iop_config.h>
#include "LayerUI/mainwindow.h"
#include "Net/CClientNet.h"
#include "BizLogic/CBusinessLogic.h"
#include "Message/CMsgObject.h"


int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(ui);

    QApplication a(argc, argv);

    WSADATA wsadata;
    WSAStartup(MAKEWORD( 2, 2 ),&wsadata);

    MainWindow ui;
    CClientNet cn;
    CBusinessLogic bl;
    ui.show();

    CModuleAgent *ma = CModuleAgent::getUniqueAgent();

    ma->registerModule("UI", &ui);
    ma->registerModule("BIZ", &bl);
    ma->registerModule("NET", &cn);

    ui.addReceiver(&bl);		// UI
    cn.addReceiver(&bl);        // CN

    if (argc > 2) {
        cn.SetServerAddr(0, argv[1], atoi(argv[2]));
    } else {
        cn.SetServerAddr(0, "192.168.1.202", 2222);
    }
    cn.Start(0);

    return a.exec();
}
