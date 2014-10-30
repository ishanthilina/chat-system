#include "Message.h"

static const char * EnumStrings[] = { "LIN;", "PTP;", "LOU;", "NTF;", "AUT;" };

const char * GetTextForEnum( int iEnumVal )
{
	return EnumStrings[iEnumVal];
}

const MessageType GetEnumFromString(string sEnumStr){
	MessageType oReturnType;
	bool bReturnTypeWasSet=false;
	for (int i=0; i<5;i++){
		if (sEnumStr.compare(EnumStrings[i])==0)
		{
			oReturnType=static_cast<MessageType>(i);
			bReturnTypeWasSet=true;
			break;
		}

	}
	if (!bReturnTypeWasSet)
	{
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
	return p_Receivers;
}



bool Message::IsMessageComplete()
{
	if(s_EncodedMessage.length()==i_MsgLength)
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
		iRetVal=(*it)->SendMessage(s_EncodedMessage);


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
	s_EncodedMessage = sEncodedMessage;
	s_Message = sMessage;
	p_Server = pServer;
	p_Client = pClient;
	p_TargetUsers = pTargetUsers;
}

Message::Message(string sEncodedMessage, Server* pServer, Client* pClient)
{
	LogDebug("Message.cpp : Creating message using the string : %s", sEncodedMessage.c_str());
	s_EncodedMessage = sEncodedMessage;
	p_Server = pServer;
	p_Client = pClient;

	//set the expected message length
	string sMsgLength = sEncodedMessage.substr(GetMessageHeader().length(),GetMessageLengthSectionLength()-1);
	const char* pzMsgLength=sMsgLength.c_str();
	i_MsgLength=atoi(pzMsgLength);


	//set the message type
	e_MessageType = GetEnumFromString(sEncodedMessage.substr(GetMessageHeader().length()+GetMessageLengthSectionLength(), GetProtocolLength()));


	//if the message is complete, extract the message content
	if(IsMessageComplete())
	{
		ProcessMessage();
	}

	
	b_ValidMessage=true;

}

bool Message::sendMessageToClient()
{
	int iRetVal;
	bool bSendSuccess=true;

	iRetVal=p_Client->SendMessage(s_EncodedMessage);


	if(iRetVal)
	{
		LogDebug("Message.cpp :Sent to Client : %s.",s_EncodedMessage.c_str());
	}
	else
	{
		bSendSuccess = false;
		LogDebug("Message.cpp :Error sending to Client : %s.",s_EncodedMessage.c_str());
	}

	return bSendSuccess;


}

bool Message::sendMessageToClient( string sMsg )
{
	int iRetVal;
	bool bSendSuccess=true;

	iRetVal=p_Client->SendMessage(sMsg);


	if(iRetVal)
	{
		LogDebug("Message.cpp :Sent to Client : %s.",s_EncodedMessage.c_str());
	}
	else
	{
		bSendSuccess = false;
		LogDebug("Message.cpp :Error sending to Client : %s.",s_EncodedMessage.c_str());
	}

	return bSendSuccess;
}

bool Message::IsValidMessage() {

	if(s_EncodedMessage.length()>i_MsgLength){
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
	//|;|0000028|PTP;12;wwwwwww|;|
	if(e_MessageType == DIRECT)
	{
		int iMsgStartLocation = GetMessageHeader().length()+GetMessageLengthSectionLength()+ GetProtocolLength();

				//find the ending location of the receivers list in the message
				int iReceiverListEndLoc=s_EncodedMessage.substr(iMsgStartLocation).find_first_of(";");
				//LogDebug("iReceiverListEndLoc %d",iReceiverListEndLoc);
				string sReceivers = s_EncodedMessage.substr(iMsgStartLocation,iReceiverListEndLoc);
				//get all the receiver names
				p_Receivers = new vector<string>;
				std::size_t iPrev = 0, iPos;
				while ((iPos = sReceivers.find_first_of(",", iPrev)) != std::string::npos)
				{
					if ( iPos > iPrev){
						LogDebug("Adding Receiver: %s",sReceivers.substr(iPrev, iPos-iPrev).c_str());
						p_Receivers->push_back(sReceivers.substr(iPrev, iPos-iPrev));
					}
					iPrev = iPos+1;


				}

				//fetch the last name also
				if (iPrev < iReceiverListEndLoc)
				{
					LogDebug("Adding Receiver: %s",sReceivers.substr(iPrev, iReceiverListEndLoc-iPrev).c_str());
					p_Receivers->push_back(sReceivers.substr(iPrev, iReceiverListEndLoc-iPrev));
				}



				s_Message = s_EncodedMessage.substr(iReceiverListEndLoc+iMsgStartLocation+1, s_EncodedMessage.substr(iReceiverListEndLoc+iMsgStartLocation+1).find_first_of("|"));
				//LogDebug("%s", s_Message.c_str());

	}
	//|;|0000019|LIN;1|;|
	else if (e_MessageType == LOGIN)
	{
		//get the senders login name
		

		//find the starting location of the senders username
		int iMsgStartLocation = GetMessageHeader().length()+GetMessageLengthSectionLength()+ GetProtocolLength();
		int iSenderNameEndLoc=s_EncodedMessage.substr(iMsgStartLocation).find_first_of("|");

		s_Message = s_EncodedMessage.substr(iMsgStartLocation, iSenderNameEndLoc);

	}

}
