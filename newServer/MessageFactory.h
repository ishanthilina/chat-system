#ifndef _MESSAGE_FACTORY_HEADER_
#define _MESSAGE_FACTORY_HEADER_

#include <string>
#include <iostream>
#include <vector>
#include <netinet/in.h>	//for sockaddr_in
#include "Message.h"
#include "Utils.h"

using namespace std;

class MessageFactory
{
public:
	Message * createMessage(int i_sender, string s_Message, sockaddr_in o_SenderSockAddr);
	MessageFactory();
protected:
private:
	MessageType getMessageType(string s_Message);

	char c_MessageSeperator;
};

#endif //_MESSAGE_FACTORY_HEADER_
