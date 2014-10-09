#include "ScreenWriter.h"


void ScreenWriter::WriteChatMessage( string sMessage )
{
	cout<<"[CHAT-MESSAGE] "<<sMessage<<endl;
}

void ScreenWriter::WriteNotificationMessage( string sMessage )
{
	cout<<"[NOTIFICATION] "<<sMessage<<endl;
}

ScreenWriter::ScreenWriter()
{
	this->WriteNotificationMessage("Please enter the username: ");
}
