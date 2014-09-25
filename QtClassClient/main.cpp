#include <QApplication>
#include "LayerUI/mainwindow.h"
#include "Net/CClientNet.h"
#include "BizLogic/CBusinessLogic.h"
#include "Message/CMsgObject.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow *ui = new MainWindow();
    ui->show();

    CClientNet* cn = new CClientNet();

    CBusinessLogic* bl = new CBusinessLogic();

    ui->addDownReceiver(bl);		// UI
    bl->addDownReceiver(cn);		// BL
    bl->addUpReceiver(ui);			// CN
    cn->addUpReceiver(bl);			// 三层，从上往下

    return a.exec();
}
