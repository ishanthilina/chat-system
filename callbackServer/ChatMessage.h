#ifndef _CHAT_MESSAGE_HEADER_
#define _CHAT_MESSAGE_HEADER_

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
	vector<string> * GetReceivers();
	bool SendMessageToReceivers();
	bool sendMessageToClient();
	bool sendMessageToClient(string sMsg);
	
	ChatMessage(string sEncodedMessage, string sMessage, Server* pServer, Client* pClient, vector<User*> *pTargetUsers);
	ChatMessage(Message* pMessage);
protected:
	void ProcessMessage();
private:

	MessageType e_MessageType;
	vector<string> * p_Receivers;
	vector<User*> *p_TargetUsers;

};


#endif	//_CHAT_MESSAGE_HEADER_