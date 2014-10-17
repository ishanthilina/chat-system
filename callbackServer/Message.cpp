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


vector<string> * Message::GetReceivers()
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


bool Message::SendMessageToReceivers()
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
	LogDebug("Message.cpp : Creating message(with target users) using the string : %s", sEncodedMessage.c_str());
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
		this->ProcessMessage();
	}

	this->b_ValidMessage=true;

}

bool Message::sendMessageToClient()
{
	int iRetVal;
	bool bSendSuccess=true;

	iRetVal=p_Client->SendMessage(this->s_EncodedMessage);


	if(iRetVal)
	{
		LogDebug("Message.cpp :Sent to Client : %s.",this->s_EncodedMessage.c_str());
	}
	else
	{
		bSendSuccess = false;
		LogDebug("Message.cpp :Error sending to Client : %s.",this->s_EncodedMessage.c_str());
	}

	return bSendSuccess;


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
		this->ProcessMessage();
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

void Message::ProcessMessage()
{

	if(this->e_MessageType == DIRECT)
	{
		int iMsgStartLocation = GetMessageHeader().length()+GetMessageLengthSectionLength()+ GetProtocolLength();
		//LogDebug("iMsgStartLocation %d",iMsgStartLocation);

		//|;|0000028|PTP;12;wwwwwww|;|

				//find the ending location of the receivers list in the message
				int iReceiverListEndLoc=this->s_EncodedMessage.substr(iMsgStartLocation).find_first_of(";");
				//LogDebug("iReceiverListEndLoc %d",iReceiverListEndLoc);
				string sReceivers = this->s_EncodedMessage.substr(iMsgStartLocation,iReceiverListEndLoc);
				//LogDebug("Receivers: %s",sReceivers.c_str());
				//get all the receiver names
				this->o_Receivers = new vector<string>;
				std::size_t iPrev = 0, iPos;
				while ((iPos = sReceivers.find_first_of(",", iPrev)) != std::string::npos)
				{
				//	LogDebug("Found , at : %d", iPos);
					if ( iPos > iPrev){
						LogDebug("Adding Receiver: %s",sReceivers.substr(iPrev, iPos-iPrev).c_str());
						o_Receivers->push_back(sReceivers.substr(iPrev, iPos-iPrev));
					}
					iPrev = iPos+1;


				}

				//fetch the last name also
				if (iPrev < iReceiverListEndLoc)
				{
					LogDebug("Adding Receiver: %s",sReceivers.substr(iPrev, iReceiverListEndLoc-iPrev).c_str());
					o_Receivers->push_back(sReceivers.substr(iPrev, iReceiverListEndLoc-iPrev));
				}



				this->s_Message = this->s_EncodedMessage.substr(iReceiverListEndLoc+iMsgStartLocation+1, this->s_EncodedMessage.substr(iReceiverListEndLoc+iMsgStartLocation+1).find_first_of("|"));
				//LogDebug("%s", s_Message.c_str());

	}
	else if (this->e_MessageType == LOGIN)
	{
		//get the senders login name
		//|;|0000019|LIN;1|;|

		//find the starting location of the senders username
		int iMsgStartLocation = GetMessageHeader().length()+GetMessageLengthSectionLength()+ GetProtocolLength();
		int iSenderNameEndLoc=this->s_EncodedMessage.substr(iMsgStartLocation).find_first_of("|");
		//LogDebug("%d",iMsgStartLocation);
		//LogDebug("%d",iSenderNameEndLoc);
		this->s_Message = this->s_EncodedMessage.substr(iMsgStartLocation, iSenderNameEndLoc);

	}

}
