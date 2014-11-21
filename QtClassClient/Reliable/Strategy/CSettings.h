#ifndef _STRATEGY_CSETTINGS_H_
#define _STRATEGY_CSETTINGS_H_


#include <iop_util.h>

void settingsServerSocketOpt(io_handle_t h);

bool controlReliableConnect(int currentMissingRate);


#endif