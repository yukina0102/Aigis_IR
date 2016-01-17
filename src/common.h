#ifndef __COMMON_H__
#define __COMMON_H__

#pragma comment(lib,"Gdi32.lib")
#pragma comment(lib,"User32.lib")
#pragma comment(lib,"Dwmapi.lib")

#include <tchar.h>
#include <windows.h>

#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <boost/variant.hpp>

#include "Common\tString.h"
#include "SubModule\wcwidth\wcwidth.h"

#include "Common\opencv_common.h"
#include "Common\sqlite_common.h"

#include "Define.h"

#endif/*__COMMON_H__*/