#ifndef _STDAFX_H_
#define _STDAFX_H_

#include <stdint.h>

typedef uint64_t		TS_UINT64;

//#define _DEBUG_INFO_

#ifdef WIN32
#pragma comment(lib, "ws2_32.lib")
#endif

#define DESTROY(p) if (NULL != (p)) { delete (p); (p) = NULL; }

#endif
