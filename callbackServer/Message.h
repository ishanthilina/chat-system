#ifndef _MESSAGE_HEADER_
#define _MESSAGE_HEADER_

#include <string>
#include <iostream>
#include <netinet/in.h>	//for sockaddr_in

#include "Client.h"
#include "Server.h"
#include "User.h"
#include "Utils.h"


using namespace std;

// Message format:
// |;|Length of the message in 7 digits|Message content|;|
// ex -
// |;|0000019|LIN;1|;|


string GetMessageHeader();
string GetMessageFooter();
int GetTotalHeaderLength();
int GetTotalFooterLength();
int GetMessageLengthSectionLength();




class Message
{
public:
	char* GetMessage();
	char* GetEncodedMessage();

	Client * GetClient();
	Server* GetServer();
	bool IsMessageComplete();
	void FillMessage(char* sMessage);
	bool IsValidMessage();
	bool IsNetworkMessage();
	
	Message(char* sEncodedMessage, int iMsgLength, Server* pServer, Client* pClient);
	Message(char* sMessage);

protected:
	void ProcessMessage();

	char* s_EncodedMessage;
	char* s_Message;

	Server* p_Server;
	Client* p_Client;
private:
	
	void EncodeMessage();
	

	int i_ExpectedMsgLength;
	int i_CurrentMsgLength;
	bool b_ValidMessage;
	bool b_NetworkMessage;

};


#endif	//_MESSAGE_HEADER_

