#include <iostream>
#include <iop_util.h>
#include "../../QtClassClient/Reliable/Server/CAgentServer.h"
#include "../../QtClassClient/Reliable/Server/CWSServer.h"

using namespace std;

int main(int argc, char* argv[]) {
	SOCK_STARTUP();
	
	CAgentServer* temp = new CAgentServer();
	temp->Start(2222);

	while (true) { Sleep(1000); };

	SOCK_CLEANUP();
	return 0;
}