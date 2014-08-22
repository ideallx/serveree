#include <iostream>
#include <iop_util.h>
#include "Server\CWSServer.h"

using namespace std;


int main(int argc, char* argv[]) {
	SOCK_STARTUP();
	
	CWSServer* temp = new CWSServer(1, 2);
	temp->Start(2222);

	while (true) {};

	SOCK_CLEANUP();
	return 0;

}