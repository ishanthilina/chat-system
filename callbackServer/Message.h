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
	NOTIFICATION=3,
	AUTHENTICATION=4,
	ERROR=5 //denotes a message type with an error
};

const char * GetTextForEnum( int );
const MessageType GetEnumFromString(string);

string GetMessageHeader();
string GetMessageFooter();
int GetTotalHeaderLength();
int GetTotalFooterLength();
int GetMessageLengthSectionLength();



class Message
{
public:
	Message(string s_Message, MessageType e_MessageType, int i_Sender, vector<string> * o_Receivers, sockaddr_in o_SenderSockAddr);
	string GetMessage();
	MessageType GetMessageType();
	vector<string> * getReceivers();
	Client * GetClient();
	Server* GetServer();
	int SendMessage();

	Message(string sEncodedMessage, Server* pServer, Client* pClient);
	bool IsMessageComplete();
	void FillMessage(string sMessage);
	bool IsValidMessage();
	string GetEncodedMessage();
protected:
private:
	string s_Message;
	MessageType e_MessageType;
	vector<string> * o_Receivers;

	Server* p_Server;
	Client* p_Client;

	int i_MsgLength;
	bool b_ValidMessage;
	string s_EncodedMessage;
};


#endif	//_MESSAGE_HEADER_

