#ifndef _PATH_H_
#define _PATH_H_

#pragma once

#include "Common/tString.h"

struct DirPath
{
	static const tstring TEMPIMAGE_BASE;

	static const tstring UNIT_GLOBAL;
	static const tstring UNIT_LOCAL;
	static const tstring STAGE_GLOBAL;
	static const tstring STAGE_LOCAL;
	static const tstring ITEM_LOCAL;
	static const tstring ITEM_GLOBAL;

};

struct DBPath
{
	static const tstring RESULT;

	static const tstring UNIT_GLOBAL;
	static const tstring UNIT_LOCAL;
	static const tstring STAGE_GLOBAL;
	static const tstring STAGE_LOCAL;
	static const tstring ITEM_LOCAL;
	static const tstring ITEM_GLOBAL;

};

#endif/*_PATH_H_*/