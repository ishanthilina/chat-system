#include "Message.h"

static const char * EnumStrings[] = { "LIN;", "PTP;", "LOU;", "NTF;", "AUT;" };

const char * GetTextForEnum( int i_EnumVal )
{
	return EnumStrings[i_EnumVal];
}

const MessageType GetEnumFromString(string s_EnumStr){
	MessageType oReturnType;
	bool bReturnTypeWasSet=false;
	for (int i=0; i<5;i++){
		if (s_EnumStr.compare(EnumStrings[i])==0)
		{
			oReturnType=static_cast<MessageType>(i);
			bReturnTypeWasSet=true;
			//cout<<i;
			break;
		}
		//cout<<"No : "<<i<<":"<<s_EnumStr;
	}
	if (!bReturnTypeWasSet)
	{
		//cout<<"ErroR";
		oReturnType=ERROR;
	}

	return oReturnType;
}

std::string GetMessageHeader()
{
	return string("|;|");
}

std::string GetMessageFooter()
{
	return string("|;|");
}

int GetTotalHeaderLength()
{
	return 11;
}

int GetTotalFooterLength()
{
	return 3;
}

Message::Message(string s_Message, MessageType e_MessageType, int i_Sender, vector<string> * o_Receivers, sockaddr_in o_SenderSockAddr)
{

	this->s_Message = s_Message;
	this->e_MessageType = e_MessageType;
	this->o_Receivers = o_Receivers;
	this->i_SenderSocket = i_Sender;
	this->o_SenderSockAddr=o_SenderSockAddr;

}

string Message::GetMessage()
{
	return s_Message;

}

MessageType Message::GetMessageType()
{
	return e_MessageType;
}


vector<string> * Message::getReceivers()
{
	return o_Receivers;
}


Message::Message(string sEncodedMessage, Server* pServer, Client* pClient)
{
	this->s_EncodedMessage = sEncodedMessage;
	this->p_Client=pClient;
	this->p_Server=pServer;
}

bool Message::IsMessageComplete()
{
	if(this->s_EncodedMessage.length()==this->i_MsgLength)
	{
		return true;
	}

	return false;
}

int Message::SendMessage()
{
	return 0;
}

bool Message::IsValidMessage() {

	if(this->s_EncodedMessage.length()>this->i_MsgLength){
		this->b_ValidMessage=false;
	}

	return b_ValidMessage;
}

void Message::FillMessage(string sMessage)
{
	if(!IsMessageComplete() && IsValidMessage()){
		this->s_EncodedMessage.append(sMessage);
	}


}

string BufferredMessage::GetEncodedMessage()
{
	return s_Message;
}

Client* Message::GetClient()
{
	return this->p_Client;
}

Server* Message::GetServer()
{
	return this->p_Server;
}
