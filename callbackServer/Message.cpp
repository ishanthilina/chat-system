#include "Message.h"



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

int GetMessageLengthSectionLength()
{
	return 8;
}

int GetProtocolLength()
{
	return 4;
}


char* Message::GetMessage()
{
	return s_Message;

}





bool Message::IsMessageComplete()
{
	if(i_CurrentMsgLength == i_ExpectedMsgLength)
	{
		return true;
	}

	return false;
}





Message::Message(char* sEncodedMessage, int iMsgLength, Server* pServer, Client* pClient)
{
	LogDebug("Message.cpp : Creating message using the string : %s", sEncodedMessage.c_str());
	s_EncodedMessage = sEncodedMessage;
	i_CurrentMsgLength = iMsgLength;
	p_Server = pServer;
	p_Client = pClient;

	//set the expected message length
	string sMsgLength = sEncodedMessage.substr(GetMessageHeader().length(),GetMessageLengthSectionLength()-1);
	const char* pzMsgLength=sMsgLength.c_str();
	i_ExpectedMsgLength=atoi(pzMsgLength);
	
	b_ValidMessage=true;

	//if the message is complete, extract the message content
	if(IsMessageComplete())
	{
		ProcessMessage();
	}

}

Message::Message( string sMessage )
{
	s_Message = sMessage;
	EncodeMessage();
}


bool Message::IsValidMessage() {

	if(s_EncodedMessage.length()>i_ExpectedMsgLength){
		LogDebug("Message.cpp: Message is invalid. s_EncodedMessage.length: %d, i_MsgLength: %d",s_EncodedMessage.length(),i_ExpectedMsgLength);
		b_ValidMessage=false;
	}

	return b_ValidMessage;
}

void Message::FillMessage(string sMessage)
{
	if(!IsMessageComplete() && IsValidMessage()){
		s_EncodedMessage.append(sMessage);
	}

	//if the message is complete, extract the message content
	if(IsMessageComplete())
	{
		ProcessMessage();
	}


}

string Message::GetEncodedMessage()
{
	return s_EncodedMessage;
}

Client* Message::GetClient()
{
	return p_Client;
}

Server* Message::GetServer()
{
	return p_Server;
}

void Message::ProcessMessage()
{
	if (IsValidMessage() && IsMessageComplete())
	{
		s_Message = s_EncodedMessage.substr(GetTotalHeaderLength(),(i_ExpectedMsgLength-(GetTotalHeaderLength()+GetTotalFooterLength())));
	}
	else{
		LogDebug("Message.cpp: Cannot process non-valid message");
	}
}

bool Message::IsNetworkMessage()
{
	return b_NetworkMessage;
}

void Message::EncodeMessage()
{
	//get total message length
	int iMsgLength = GetMessageHeader().length()+GetMessageLengthSectionLength()+s_Message.length()+GetMessageFooter().length();
	char zBuf[4];
	memset(zBuf, 0, 4);
	sprintf(zBuf, "%d", iMsgLength);
	string sMsgLength=string(zBuf);
	while (sMsgLength.length()<7)	//set the length of message header items length constant
	{
		sMsgLength.insert(0,"0");
	}

	string sNotifMsg=GetMessageHeader();
	sNotifMsg.append(sMsgLength);
	sNotifMsg.append("|");
	sNotifMsg.append(s_Message);
	sNotifMsg.append(GetMessageFooter());
	s_EncodedMessage = sNotifMsg;
}

