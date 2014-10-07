#include "Logger.h"

void Logger::LogEvent( Client * o_Client, string s_Message )
{
	//cout<<"Logging: "<<s_Message;

	ofstream myfile;
	myfile.open (o_Client->GetLogName().c_str(), ios::out | ios::app);
	myfile << s_Message.c_str();
	myfile.close();

}
