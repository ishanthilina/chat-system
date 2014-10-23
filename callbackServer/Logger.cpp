#include "Logger.h"

void Logger::LogEvent( User * pUser, string sMessage )
{
	LogDebug("Logger.cpp - Logging message %s", sMessage.c_str());
	ofstream oMyFile;
	oMyFile.open (pUser->GetLogName().c_str(), ios::out | ios::app);
	oMyFile << sMessage.c_str()<<endl;
	oMyFile.close();

}
