/*
 * Utils.cpp
 *
 *  Created on: Oct 8, 2014
 *      Author: ishan
 */

#include "Utils.h"

bool gb_IsDebugOn = true;

void LogDebug(const char* zFormat, ...)
{
	if (gb_IsDebugOn)
	{
		va_list oArglist;

		va_start( oArglist, zFormat );
		printf("[DEBUG] ");
		vprintf( zFormat, oArglist );
		va_end( oArglist );
		printf("\n");
	}
}

