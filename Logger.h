#ifndef _LOGGER_HEADER_
#define _LOGGER_HEADER_

#include <string>

#include "Client.h"

using namespace std;

class Logger
{
public:
	void LogEvent(Client * o_Client, string s_Message);
protected:
private:
};

#endif