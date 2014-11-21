#include <iostream>

#include "CSettings.h"

using namespace std;

void settingsServerSocketOpt(io_handle_t h) {
	iop_sock_reuseaddr(h);
}

// if missing rate is more than 30% we need contrl reliable connect
bool controlReliableConnect(int currentMissingRate) {
	if (currentMissingRate > 300) {
		cout << "current Missing Rate:" << currentMissingRate << endl;
		return true;
	}
	return false;
}