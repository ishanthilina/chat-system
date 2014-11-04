#include "Logger.h"

bool gb_IsLoggingOn = true;

void Logger::LogEvent( User * pUser, const char* zFormat, ... )
{

	if (gb_IsLoggingOn)
		{
			va_list oArglist;

			va_start( oArglist, zFormat );

			FILE * pFile;
			pFile = fopen (pUser->GetLogName().c_str(),"w");

			vfprintf (pFile, zFormat, oArglist);
			va_end( oArglist );

		}


}

Logger::Logger()
{

}
