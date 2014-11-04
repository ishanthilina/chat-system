#ifndef _CHAT_MESSAGE_HEADER_
#define _CHAT_MESSAGE_HEADER_

#include <list>

#include "Message.h"

enum MessageType
{
	LOGIN = 0,
	DIRECT=1,
	LOGOUT=2,
	NOTIFICATION=3,
	AUTHENTICATION=4,
	ERROR=5 //denotes a message type with an error
};

const char * GetTextForEnum( int );
const MessageType GetEnumFromString(string);

int GetProtocolLength();

class ChatMessage : public Message
{
public:
	MessageType GetMessageType();
	list<string> * GetReceivers();
	bool SendMessageToReceivers();
	bool sendMessageToClient();
	bool sendMessageToClient(string sMsg);
	
	ChatMessage(string sEncodedMessage, string sMessage, Server* pServer, Client* pClient, list<User*> *pTargetUsers);
	ChatMessage(Message* pMessage);
protected:
	void ProcessMessage();
private:

	MessageType e_MessageType;
	list<string> * p_Receivers;
	list<User*> *p_TargetUsers;

};


#endif	//_CHAT_MESSAGE_HEADER_
