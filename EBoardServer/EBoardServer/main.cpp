#include <iostream>
#include <iop_util.h>
#include "Server\CAgentServer.h"

#include "Server\CWSServer.h"

using namespace std;

int main(int argc, char* argv[]) {
	SOCK_STARTUP();
	
	CAgentServer* temp = new CAgentServer();
	temp->Start(2222);

	while (true) { Sleep(1000); };

	SOCK_CLEANUP();
	return 0;
}