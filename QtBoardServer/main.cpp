#include <QCoreApplication>

#include <iostream>
#include <iop_util.h>
#include "Server\CAgentServer.h"

#include "Server\CWSServer.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    SOCK_STARTUP();

    CAgentServer* temp = new CAgentServer();
    temp->Start(2222);

    while (true) {};

    SOCK_CLEANUP();
    return 0;

    return a.exec();
}
