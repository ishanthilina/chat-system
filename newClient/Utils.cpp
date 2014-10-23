/*
 * Utils.cpp
 *
 *  Created on: Oct 8, 2014
 *      Author: ishan
 */

#include "Utils.h"

bool gb_IsDebugOn = true;

void LogDebug(const char* zpFormat, ...)
{
	if (gb_IsDebugOn)
	{
		//append a new line
		size_t iLen = strlen(zpFormat);
		char* zpRet = new char[iLen+2];
		strcpy(zpRet, zpFormat);
		zpRet[iLen] = '\n';
		zpRet[iLen+1] = '\0';

		va_list sArglist;

		va_start( sArglist, zpRet );
		printf("[DEBUG] ");
		vprintf( zpRet, sArglist );
		va_end( sArglist );
	}
}

