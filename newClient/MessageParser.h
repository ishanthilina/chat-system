#ifndef _MESSAGE_PARSER_HEADER_
#define _MESSAGE_PARSER_HEADER_


#include <string>
#include <stdio.h>
#include <iostream>
#include <cstring>


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

class MessageParser
{
public:
	int CreateLoginMessage(string * spMessageContent);
	int CreateChatMessage(string * spMessageContent);
	MessageType GetMessageType(string sMessageContent);
	string GetMessageContent(string sMessageContent);
protected:
private:
};

#endif  //_MESSAGE_PARSER_HEADER_
