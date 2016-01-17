#ifndef __OUTPUTDEVICE_H__
#define __OUTPUTDEVICE_H__

#pragma once

#include "common.h"

enum class DisplayLevel {
	NO_DISPLAY,
	ERRORS,
	RESULTS,
	PROGRESSION,
	INFORMATION,
	DEVELOPMENT,
	MIN = NO_DISPLAY,
	MAX = INFORMATION,
	DEFAULT = RESULTS,
};


class OutputDevice
{


public:
	void Console( void )
	{
		
	}
};


#endif/*__OUTPUTDEVICE_H__*/