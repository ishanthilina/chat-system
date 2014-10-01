#ifndef _MESSAGE_FACTORY_HEADER_
#define _MESSAGE_FACTORY_HEADER_

#include <string>
#include "Message.h"

using namespace std;

class MessageFactory
{
public:
	Message createMessage(int i_sender, string s_Message);
	MessageFactory();
protected:
private:
	MessageType getMessageType(string s_Message);

	char c_MessageSeperator;
};

#endif //_MESSAGE_FACTORY_HEADER_