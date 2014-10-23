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
		//append a new line
		size_t iLen = strlen(zFormat);
		char* zRet = new char[iLen+2];
		strcpy(zRet, zFormat);
		zRet[iLen] = '\n';
		zRet[iLen+1] = '\0';

		va_list oArglist;

		va_start( oArglist, zRet );
		printf("[DEBUG] ");
		vprintf( zRet, oArglist );
		va_end( oArglist );
	}
}

