#include <iop_config.h>

#include "BeforeClass/totalprocess.h"

#include <QApplication>

//#include <Windows.h>
//typedef BOOL (WINAPI *pSDARP)(ORIENTATION_PREFERENCE orientation);
//pSDARP pARP;


int program(int argc, char *argv[]) {
    QApplication a(argc, argv);

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

int before(int argc, char *argv[]) {
    QApplication a(argc, argv);
    LoginDialog ld;
    ld.show();
    return a.exec();
}

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(ui);
    SOCK_STARTUP();

    QApplication a(argc, argv);

    TotalProcess tp(argc, argv);
    int result = a.exec();

    SOCK_CLEANUP();

    return result;
}
