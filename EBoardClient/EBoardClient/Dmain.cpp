#include <iostream>
#include <iop_util.h>
#include "Server\DWSClient.h"

using namespace std;


int main(int argc, char* argv[]) {
	SOCK_STARTUP();
	
	DWSClient* temp = new DWSClient(1, 2);
	temp->Start(2222);

	while (true) {};

	SOCK_CLEANUP();
	return 0;
}