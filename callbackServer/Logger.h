#ifndef _LOGGER_HEADER_
#define _LOGGER_HEADER_

#include <string>
#include <stdio.h>
#include <fstream>
#include "User.h"
#include "Utils.h"
#include <stdarg.h>



using namespace std;

class Logger
{
public:
	Logger();
	void LogEvent(User * pUser, const char* zFormat, ...);
protected:
private:
};

#endif //_LOGGER_HEADER_
