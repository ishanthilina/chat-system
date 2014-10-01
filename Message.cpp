#include "Message.h"

Message::Message(string s_Message, MessageType e_MessageType, int i_Sender, int i_Receiver )
{

	this->s_Message = s_Message;
	this->e_MessageType = e_MessageType;
	this->i_Receiver = i_Receiver;
	this->i_Sender = i_Sender;

}

string Message::GetMessage()
{
	return s_Message;

}

MessageType Message::GetMessageType()
{
	return e_MessageType;
}

int Message::getSender()
{

	return i_Sender;
}

int Message::getReceiver()
{
	return i_Receiver;

}




int main()
{

	return 0;
}