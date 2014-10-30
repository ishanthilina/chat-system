/*
 * Utils.cpp
 *
 *  Created on: Oct 8, 2014
 *      Author: ishan
 */

#include "Utils.h"

bool gb_IsDebugOn = false;

void LogDebug(const char* zpFormat, ...)
{
	if (gb_IsDebugOn)
	{
		va_list oArglist;

		va_start( oArglist, zpFormat );
		printf("[DEBUG] ");
		vprintf( zpFormat, oArglist );
		va_end( oArglist );
		printf("\n");
	}
}

