#include <iop_config.h>
#include "LayerUI/mainwindow.h"
#include "Net/CClientNet.h"
#include "BizLogic/CBusinessLogic.h"
#include "Message/CMsgObject.h"

#include <QApplication>
#include <QObject>
#include <QTextCodec>

//#include <Windows.h>
//typedef BOOL (WINAPI *pSDARP)(ORIENTATION_PREFERENCE orientation);
//pSDARP pARP;

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(ui);

    QApplication a(argc, argv);
    WSADATA wsadata;
    WSAStartup(MAKEWORD(2, 2),&wsadata);

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

    if (argc == 4) {
        cn.SetServerAddr(0, argv[1], 2222);
        cn.Start(0);
        ui.enterClass(argv[2], argv[3]);
    } else if (argc > 1) {
        cn.SetServerAddr(0, argv[1], 2222);
        cn.Start(0);
    } else {
        cn.SetServerAddr(0, "192.168.1.202", 2222);
        cn.Start(0);
    }

//    auto pARP = (pSDARP) GetProcAddress( GetModuleHandle(TEXT("user32.dll")),
//                                        "SetDisplayAutoRotationPreferences");
//    if (pARP) {
//        pARP((ORIENTATION_PREFERENCE)(ORIENTATION_PREFERENCE_LANDSCAPE | ORIENTATION_PREFERENCE_LANDSCAPE_FLIPPED));
//    }else{
//        printf("System not supported.\t");
//        return 1;
//    }

    ui.enterClass("teacher2", "teacher2");

    return a.exec();
}
