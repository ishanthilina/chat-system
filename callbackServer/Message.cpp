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

int GetMessageLengthSectionLength()
{
	return 8;
}

int GetProtocolLength()
{
	return 4;
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



bool Message::IsMessageComplete()
{
	if(this->s_EncodedMessage.length()==this->i_MsgLength)
	{
		return true;
	}

	return false;
}


bool Message::SendMessage()
{
	//send the message to all the recipients
	int iRetVal;
	bool bSendSuccess=true;
	for(vector<User*>::iterator it=p_TargetUsers->begin();it!=p_TargetUsers->end();++it)
	{
		LogDebug("Message.cpp :sending message to %s.",(*it)->GetUserName().c_str());
		iRetVal=(*it)->SendMessage(this->s_EncodedMessage);


		if(iRetVal)
		{
			LogDebug("Message.cpp :Message successfully sent to %s.",(*it)->GetUserName().c_str());
		}
		else
		{
			bSendSuccess = false;
			LogDebug("Message.cpp :Message send failed to %s.",(*it)->GetUserName().c_str());
		}

	}

	return bSendSuccess;

}

Message::Message(string sEncodedMessage, string sMessage, Server* pServer,
		Client* pClient, vector<User*>* pTargetUsers)
{
	LogDebug("Message.cpp : Creating message using the string : %s", sEncodedMessage.c_str());
	this->s_EncodedMessage = sEncodedMessage;
	this->s_Message = sMessage;
	this->p_Server = pServer;
	this->p_Client = pClient;
	this->p_TargetUsers = pTargetUsers;
}

Message::Message(string sEncodedMessage, Server* pServer, Client* pClient)
{
	LogDebug("Message.cpp : Creating message using the string : %s", sEncodedMessage.c_str());
	this->s_EncodedMessage = sEncodedMessage;
	this->p_Server = pServer;
	this->p_Client = pClient;

	//set the expected message length
	string sMsgLength = sEncodedMessage.substr(GetMessageHeader().length(),GetMessageLengthSectionLength()-1);
	const char* pzMsgLength=sMsgLength.c_str();
	this->i_MsgLength=atoi(pzMsgLength);

	//set the message type
	//LogDebug("ss %s", sEncodedMessage.substr(GetMessageHeader().length()+GetMessageLengthSectionLength(), 3).c_str());
	this->e_MessageType = GetEnumFromString(sEncodedMessage.substr(GetMessageHeader().length()+GetMessageLengthSectionLength(), GetProtocolLength()));



	//if the message is complete, extract the message content
	if(IsMessageComplete())
	{
		int iMsgStartLocation = GetMessageHeader().length()+GetMessageLengthSectionLength()+ GetProtocolLength();
			this->s_Message = this->s_EncodedMessage.substr(iMsgStartLocation, sEncodedMessage.length()-(iMsgStartLocation+ GetMessageFooter().length()));
	}

	this->b_ValidMessage=true;

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

	//if the message is complete, extract the message content
	if(IsMessageComplete())
	{
		int iMsgStartLocation = GetMessageHeader().length()+GetMessageLengthSectionLength()+ GetProtocolLength();
		this->s_Message = this->s_EncodedMessage.substr(iMsgStartLocation, s_EncodedMessage.length()-(iMsgStartLocation+ GetMessageFooter().length()));
	}


}

string Message::GetEncodedMessage()
{
	return s_EncodedMessage;
}

Client* Message::GetClient()
{
	return this->p_Client;
}

Server* Message::GetServer()
{
	return this->p_Server;
}
