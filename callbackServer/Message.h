#ifndef _MESSAGE_HEADER_
#define _MESSAGE_HEADER_

#include <string>
#include <iostream>
#include <vector>
#include <netinet/in.h>	//for sockaddr_in

#include "Client.h"
#include "Server.h"
#include "User.h"
#include "Utils.h"


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
int GetProtocolLength();



class Message
{
public:
	string GetMessage();
	MessageType GetMessageType();
	vector<string> * GetReceivers();
	Client * GetClient();
	Server* GetServer();
	bool SendMessageToReceivers();
	bool sendMessageToClient();
	bool sendMessageToClient(string sMsg);

	Message(string sEncodedMessage, string sMessage, Server* pServer, Client* pClient, vector<User*> *pTargetUsers);
	Message(string sEncodedMessage, Server* pServer, Client* pClient);
	bool IsMessageComplete();
	void FillMessage(string sMessage);
	bool IsValidMessage();
	string GetEncodedMessage();
protected:
private:
	string s_Message;
	MessageType e_MessageType;
	vector<string> * p_Receivers;

	Server* p_Server;
	Client* p_Client;
	vector<User*> *p_TargetUsers;

	int i_MsgLength;
	bool b_ValidMessage;
	string s_EncodedMessage;

	void ProcessMessage();

};


#endif	//_MESSAGE_HEADER_

