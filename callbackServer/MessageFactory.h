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
	Message * createChatMessage(string sMessage, Server* pReceivedServer, Client* pClient, vector<string>* pReceivers);
	Message* CreateAuthStatusMessage(bool bAuthStatus,Server* pReceivedServer, Client* pClient);
	MessageFactory();
protected:
private:
	MessageType getMessageType(string s_Message);
	string CreateEncodedMessageString(MessageType eMessageType,string s_Message);
	UserRegistry* pUserRegistry;

	char c_MessageSeperator;
};

#endif //_MESSAGE_FACTORY_HEADER_
