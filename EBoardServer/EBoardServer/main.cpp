#include <iostream>
#include <iop_util.h>
#include "Server\CAgentServer.h"

using namespace std;


int main(int argc, char* argv[]) {
	SOCK_STARTUP();
	
	CAgentServer* temp = new CAgentServer();
	temp->Start(2222);

	while (true) {};

	SOCK_CLEANUP();
	return 0;

}