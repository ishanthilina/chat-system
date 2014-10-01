#ifndef _MESSAGE_HEADER_
#define _MESSAGE_HEADER_

#include <string>

using namespace std;

enum MessageType
{
	LOGIN = 0,
	DIRECT=1
};

class Message
{
public:
	Message(string s_Message, MessageType e_MessageType, int i_Sender, int i_Receiver);
	string GetMessage();
	MessageType GetMessageType();
	int getSender();
	int getReceiver();
protected:
private:
	string s_Message;
	MessageType e_MessageType;
	int i_Sender;
	int i_Receiver;
};


#endif	//_MESSAGE_HEADER_

