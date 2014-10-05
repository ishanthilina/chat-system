#ifndef _UTILS_HEADER_
#define _UTILS_HEADER_

#include <stdarg.h>
#include <stdio.h>



bool gb_IsDebugOn = true;

void LogDebug(const char* format, ...)
{
	if (gb_IsDebugOn)
	{
		va_list arglist;

		va_start( arglist, format );
		vprintf( format, arglist );
		va_end( arglist );
	}	
}

#endif	//_UTILS_HEADER_