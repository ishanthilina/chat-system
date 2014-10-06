#ifndef _MESSAGE_PARSER_HEADER_
#define _MESSAGE_PARSER_HEADER_


#include <string>


using namespace std;

enum MessageType
{
	LOGIN = 0,
	DIRECT=1,
	LOGOUT=2,
	DELIVERY_STATUS_REPORT=3,
	ERROR=4 //denotes a message type with an error
};

class MessageParser
{
public:
	int CreateLoginMessage(string * sMessageContent);
	int CreateChatMessage(string * sMessageContent);
	MessageType GetMessageType(string sMessageContent);
	string GetMessageContent(string sMessageContent);
protected:
private:
};

#endif  //_MESSAGE_PARSER_HEADER_