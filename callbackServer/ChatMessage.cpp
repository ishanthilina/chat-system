#include "ChatMessage.h"

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

void ChatMessage::ProcessMessage()
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
		p_Receivers = new list<string>;
		std::size_t iPrev = 0, iPos;
		while ((iPos = sReceivers.find_first_of(",", iPrev)) != std::string::npos)
		{
			if ( iPos > iPrev){
				LogDebug("ChatMessage.cpp: Adding Receiver: %s",sReceivers.substr(iPrev, iPos-iPrev).c_str());
				p_Receivers->push_back(sReceivers.substr(iPrev, iPos-iPrev));
			}
			iPrev = iPos+1;


		}

		//fetch the last name also
		if (iPrev < iReceiverListEndLoc)
		{
			LogDebug("ChatMessage.cpp: Adding Receiver: %s",sReceivers.substr(iPrev, iReceiverListEndLoc-iPrev).c_str());
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


bool ChatMessage::sendMessageToClient()
{
	int iRetVal;
	bool bSendSuccess=true;

	iRetVal=p_Client->SendMessage(this);


	if(iRetVal)
	{
		LogDebug("ChatMessage.cpp :Sent to Client : %s.",s_EncodedMessage.c_str());
	}
	else
	{
		bSendSuccess = false;
		LogDebug("ChatMessage.cpp :Error sending to Client : %s.",s_EncodedMessage.c_str());
	}

	return bSendSuccess;


}

bool ChatMessage::sendMessageToClient( string sMsg )
{
	int iRetVal;
	bool bSendSuccess=true;

	Message* pMsg = new Message(sMsg);

	iRetVal=p_Client->SendMessage(pMsg);
	delete pMsg;


	if(iRetVal)
	{
		LogDebug("ChatMessage.cpp :Sent to Client : %s.",s_EncodedMessage.c_str());
	}
	else
	{
		bSendSuccess = false;
		LogDebug("ChatMessage.cpp :Error sending to Client : %s.",s_EncodedMessage.c_str());
	}

	return bSendSuccess;
}

bool ChatMessage::SendMessageToReceivers()
{
	//send the message to all the recipients
	int iRetVal;
	bool bSendSuccess=true;
	for(list<User*>::iterator it=p_TargetUsers->begin();it!=p_TargetUsers->end();++it)
	{
		LogDebug("ChatMessage.cpp :sending message to %s.",(*it)->GetUserName().c_str());
		iRetVal=(*it)->SendMessage(s_EncodedMessage);


		if(iRetVal)
		{
			LogDebug("ChatMessage.cpp :Message successfully sent to %s.",(*it)->GetUserName().c_str());
		}
		else
		{
			bSendSuccess = false;
			LogDebug("ChatMessage.cpp :Message send failed to %s.",(*it)->GetUserName().c_str());
		}

	}

	return bSendSuccess;

}

list<string> * ChatMessage::GetReceivers()
{
	return p_Receivers;
}


MessageType ChatMessage::GetMessageType()
{
	return e_MessageType;
}

ChatMessage::ChatMessage(string sEncodedMessage, string sMessage, Server* pServer,
				 Client* pClient, list<User*>* pTargetUsers)
				 :Message(sEncodedMessage,pServer,pClient)
{
	LogDebug("ChatMessage.cpp : Creating message(with target users) using the string : %s", sEncodedMessage.c_str());
	//s_EncodedMessage = sEncodedMessage;
	s_Message = sMessage;
	//p_Server = pServer;
	//p_Client = pClient;
	p_TargetUsers = pTargetUsers;

	//set the message type
	e_MessageType = GetEnumFromString(sEncodedMessage.substr(GetMessageHeader().length()+GetMessageLengthSectionLength(), GetProtocolLength()));


	//if the message is complete, extract the message content
	if(IsMessageComplete())
	{
		ProcessMessage();
	}

}

ChatMessage::ChatMessage( Message* pMessage ):Message(pMessage->GetEncodedMessage(),pMessage->GetServer(),pMessage->GetClient())
{
	LogDebug("ChatMessage.cpp : Creating chat message using message : %s", pMessage->GetEncodedMessage().c_str());
	
	/*s_EncodedMessage = pMessage->GetEncodedMessage();
	p_Server = pMessage->GetServer();
	p_Client = pMessage->GetClient();*/

	//set the message type
	e_MessageType = GetEnumFromString(s_EncodedMessage.substr(GetMessageHeader().length()+GetMessageLengthSectionLength(), GetProtocolLength()));

	ProcessMessage();

}
