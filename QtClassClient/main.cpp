#include <iop_config.h>
#include "LayerUI/mainwindow.h"
#include "Net/CClientNet.h"
#include "BizLogic/CBusinessLogic.h"
#include "Message/CMsgObject.h"
#include "Reliable/Server/CWSServer.h"

#include <QApplication>
#include <QObject>

//#include <Windows.h>
//typedef BOOL (WINAPI *pSDARP)(ORIENTATION_PREFERENCE orientation);
//pSDARP pARP;


int program(int argc, char *argv[]) {
    QApplication a(argc, argv);
    
    MainWindow ui;
    CBusinessLogic bl;
    ui.show();

    CClientNet cn;

    CModuleAgent *ma = CModuleAgent::getUniqueAgent();

    ma->registerModule("UI", &ui);
    ma->registerModule("BIZ", &bl);
    ma->registerModule("NET", &cn);

    ui.addReceiver(&bl);		// UI
    cn.addReceiver(&bl);        // CN

    FILE* fp = freopen("config.txt", "r", stdin);
    char username[30];
    char password[30];
    char serverip[30];

    if (fp != NULL) {
        cin >> serverip >> username >> password;
        cn.SetServerAddr(0, serverip, 2222);
        ui.enterClass(username, password);
        fclose(stdin);
    } else {
        if (argc == 4) {
            cn.SetServerAddr(0, argv[1], 2222);
            ui.enterClass(argv[2], argv[3]);
        } else if (argc > 1) {
            cn.SetServerAddr(0, argv[1], 2222);
        } else {
            cn.SetServerAddr(0, "192.168.1.128", 2222);
        }
    }

//    auto pARP = (pSDARP) GetProcAddress( GetModuleHandle(TEXT("user32.dll")),
//                                        "SetDisplayAutoRotationPreferences");
//    if (pARP) {
//        pARP((ORIENTATION_PREFERENCE)(ORIENTATION_PREFERENCE_LANDSCAPE | ORIENTATION_PREFERENCE_LANDSCAPE_FLIPPED));
//    }else{
//        printf("System not supported.\t");
//        return 1;
//    }

    //ui.enterClass("teacher1", "11");
	return a.exec();
}

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(ui);
    SOCK_STARTUP();
    int result = program(argc, argv);
    SOCK_CLEANUP();
    return result;
}
