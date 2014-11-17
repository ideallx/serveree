#include "CSettings.h"

void settingsServerSocketOpt(io_handle_t h) {
	iop_sock_reuseaddr(h);
}