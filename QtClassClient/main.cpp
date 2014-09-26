#include <QApplication>
#include "LayerUI/mainwindow.h"
#include "Net/CClientNet.h"
#include "BizLogic/CBusinessLogic.h"
#include "Message/CMsgObject.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    WSADATA wsadata;
    WSAStartup(MAKEWORD( 2, 2 ),&wsadata);

    MainWindow *ui = new MainWindow();
    ui->show();

    CClientNet* cn = new CClientNet();
    CBusinessLogic* bl = new CBusinessLogic();
    CModuleAgent *ma = CModuleAgent::getUniqueAgent();

    ma->registerModule("UI", ui);
    ma->registerModule("BIZ", bl);
    ma->registerModule("NET", cn);

    ui->addReceiver(bl);		// UI
    cn->addReceiver(bl);        // CN

    cn->SetServerAddr(0, "192.168.1.202", 2222);
    cn->Start(0);

    return a.exec();
}
