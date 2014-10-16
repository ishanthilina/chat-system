#include "MessageFactory.h"


Message * MessageFactory::createMessage( int i_Sender, string s_Message, sockaddr_in o_SenderSockAddr)
{
	LogDebug("MessageFactory.cpp: Generating message for :: %s (from %d)",s_Message.c_str(), i_Sender);
	MessageType oMsgType=getMessageType(s_Message);

	Message * oMessage;
	//if this is a login message
	if(oMsgType==LOGIN)
	{
		LogDebug("MessageFactory.cpp: Login Message from  %d",i_Sender);
		oMessage=new Message(s_Message.substr(4),LOGIN,i_Sender,NULL,o_SenderSockAddr);
	}
	else if(oMsgType==DIRECT)
	{
		LogDebug("MessageFactory.cpp: Direct Message from  %d",i_Sender);
		//find the ending location of the receivers list in the message
		int iReceiverListEndLoc=s_Message.substr(4).find_first_of(";")+4;

		//get all the receiver names
		vector<string> * oReceivers = new vector<string>;
		std::size_t iPrev = 4, iPos;
		while ((iPos = s_Message.find_first_of(",", iPrev)) != std::string::npos)
		{
			if ( iPos > iPrev){
				oReceivers->push_back(s_Message.substr(iPrev, iPos-iPrev));
			}
			iPrev = iPos+1;
			

		}

		//fetch the last name also
		if (iPrev < iReceiverListEndLoc)
		{
			oReceivers->push_back(s_Message.substr(iPrev, iReceiverListEndLoc-iPrev));
		}

		oMessage=new Message(s_Message.substr(iReceiverListEndLoc+1,s_Message.length()-iReceiverListEndLoc),DIRECT,i_Sender,oReceivers,o_SenderSockAddr);
		
	}
	else if(oMsgType==LOGOUT)
		{
			LogDebug("MessageFactory.cpp: Logout Message from  %d",i_Sender);
			oMessage=new Message("Logout",LOGOUT,i_Sender,NULL,o_SenderSockAddr);
		}
	else		//else this is an invalid message
	{	
		LogDebug("MessageFactory.cpp: Error Message from  %d",i_Sender);
		oMessage=new Message(s_Message,ERROR,i_Sender,NULL,o_SenderSockAddr);
	}

	

	return oMessage;

}

MessageType MessageFactory::getMessageType( string s_Message )
{
	if(s_Message.length()<2){
		return ERROR;
	}
	string sType = s_Message.substr(0,4);

	return GetEnumFromString(sType);



}


Message * MessageFactory::createChatMessage( string sMessage, Server* pReceivedServer, Client* pClient, vector<string>* pReceivers )
{

	//set the message content (sender name + receiver names+ message)
	string sMsg;
	sMsg=pUserRegistry->GetUser(pClient)->GetUserName();
	sMsg.append(" : ");

	for(vector<string>::iterator it=pReceivers->begin();it!=pReceivers->end();++it)
	{
		//check whether the receiver exists
		if(!pUserRegistry->IsClientExists((*it))){
			LogDebug("DeliveryController.cpp :Invalid recipient %s in the message from %d.",(*it).c_str(),pClient->GetSocket());

			string sReplyMsg("Invalid recipient "+(*it));
			//send an error message
			//p_StringMsgBuilder->CreateNotificationMessage(&sReplyMsg);

			//p_SocketOperator->WriteToSocket(o_Message->GetSenderSocket(),sReplyMsg,sReplyMsg.length());

			//return;
		}
		sMsg+=(*it);
		sMsg+=",";
	}
	//delete the final ,
	sMsg.erase(sMsg.length()-1);

	sMsg.append(" : ");
	sMsg.append(sMessage);
	//p_StringMsgBuilder->CreateChatMessage(&sMsg);

	//call an internal function and build the encoded message

	LogDebug("DeliveryController.cpp :Sending message %s.",sMsg.c_str());
	LogDebug("DeliveryController.cpp :Message length %d.",sMsg.length());

	//create the full encoded message

	//set the target users

	//set the sender client

	//set the received server



	//---------------

	//construct the message to be sent
	

	
	

	
}

MessageFactory::MessageFactory()
{
	 this->c_MessageSeperator=';';
}

Message* MessageFactory::CreateAuthStatusMessage(bool bAuthStatus,
		Server* pReceivedServer, Client* pClient) {
}

// |;|7+4+2+5|LIN;ishan|;|
std::string MessageFactory::CreateEncodedMessageString( MessageType eMessageType,string s_Message )
{
	//get the protocol string
	string sProtocol(GetTextForEnum(NOTIFICATION));

	//get total message length
	int iMsgLength = GetMessageHeader().length()+GetMessageLengthSectionLength()+(sProtocol.length()+1)+s_Message.length()+GetMessageFooter().length();
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
	sNotifMsg.append(sProtocol);
	sNotifMsg.append(*sMessageContent);
	sNotifMsg.append(GetMessageFooter());
	(*sMessageContent)=sNotifMsg;
	return 0;
}
