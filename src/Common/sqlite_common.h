#ifndef __SQLITE_COMMON_H__
#define __SQLITE_COMMON_H__

#define __LIB_DLL__		(1)
//#define __LIB_STATIC__		(1)

#include <sqlite3.h>

#ifdef __LIB_DLL__
	#pragma comment( lib, "sqlite3.lib" )
#elif __LIB_STATIC__
	#include <sqlite3_staticlib.h>
#endif

#undef __LIB_DLL__
#undef __LIB_STATIC__

#endif/*__SQLITE_COMMON_H__*/