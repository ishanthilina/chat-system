#ifndef _MESSAGE_HEADER_
#define _MESSAGE_HEADER_

#include <string>
#include <iostream>
#include <vector>
#include <netinet/in.h>	//for sockaddr_in

using namespace std;

enum MessageType
{
	LOGIN = 0,
	DIRECT=1,
	LOGOUT=2,
	DELIVERY_STATUS_REPORT=3,
	ERROR=4 //denotes a message type with an error
};

const char * GetTextForEnum( int );
const MessageType GetEnumFromString(string);


class Message
{
public:
	Message(string s_Message, MessageType e_MessageType, int i_Sender, vector<string> * o_Receivers, sockaddr_in o_SenderSockAddr);
	string GetMessage();
	MessageType GetMessageType();
	int GetSenderSocket();
	sockaddr_in GetSenderSockAddr();

	vector<string> * getReceivers();
protected:
private:
	string s_Message;
	MessageType e_MessageType;
	int i_SenderSocket;
	vector<string> * o_Receivers;
	sockaddr_in o_SenderSockAddr;
};


#endif	//_MESSAGE_HEADER_

