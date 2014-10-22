#include "Logger.h"

void Logger::LogEvent( User * pUser, string s_Message )
{
	LogDebug("Logger.cpp - Logging message %s", s_Message.c_str());
	ofstream myfile;
	myfile.open (pUser->GetLogName().c_str(), ios::out | ios::app);
	myfile << s_Message.c_str()<<endl;
	myfile.close();

}
