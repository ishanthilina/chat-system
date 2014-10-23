#ifndef _LOGGER_HEADER_
#define _LOGGER_HEADER_

#include <string>
#include <iostream>
#include <fstream>
#include "User.h"
#include "Utils.h"



using namespace std;

class Logger
{
public:
	void LogEvent(User * pUser, string sMessage);
protected:
private:
};

#endif //_LOGGER_HEADER_
