/*
 * Utils.cpp
 *
 *  Created on: Oct 8, 2014
 *      Author: ishan
 */

#include "Utils.h"

bool gb_IsDebugOn = false;

void LogDebug(const char* format, ...)
{
	if (gb_IsDebugOn)
	{
		//append a new line
		size_t len = strlen(format);
		char* ret = new char[len+2];
		strcpy(ret, format);
		ret[len] = '\n';
		ret[len+1] = '\0';

		va_list arglist;

		va_start( arglist, ret );
		printf("[DEBUG] ");
		vprintf( ret, arglist );
		va_end( arglist );
	}
}

