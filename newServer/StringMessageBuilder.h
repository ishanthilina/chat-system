#ifndef _STRING_MESSAGE_BUILDER_HEADER_
#define _STRING_MESSAGE_BUILDER_HEADER_


#include <string>
#include <stdio.h>
#include <cstring>


#include "Message.h"


using namespace std;



class StringMessageBuilder
{
public:
	//notifies about user disconnects, new user joins, etc.
	int CreateNotificationMessage(string * sMessageContent);
	//PTP messages
	int CreateChatMessage(string * sMessageContent);
	//Authentication status message
	string CreateAuthStatusMessage(bool bAuthStatus);
	//MessageType GetMessageType(string sMessageContent);
	//string GetMessageContent(string sMessageContent);
protected:
private:
};

#endif  //_STRING_MESSAGE_BUILDER_HEADER_
