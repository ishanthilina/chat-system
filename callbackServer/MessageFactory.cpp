#include "MessageFactory.h"


//Message * MessageFactory::createMessage( int i_Sender, string s_Message, sockaddr_in o_SenderSockAddr)
//{
//	LogDebug("MessageFactory.cpp: Generating message for :: %s (from %d)",s_Message.c_str(), i_Sender);
//	MessageType oMsgType=getMessageType(s_Message);
//
//	Message * oMessage;
//	//if this is a login message
//	if(oMsgType==LOGIN)
//	{
//		LogDebug("MessageFactory.cpp: Login Message from  %d",i_Sender);
//		oMessage=new Message(s_Message.substr(4),LOGIN,i_Sender,NULL,o_SenderSockAddr);
//	}
//	else if(oMsgType==DIRECT)
//	{
//		LogDebug("MessageFactory.cpp: Direct Message from  %d",i_Sender);
//		//find the ending location of the receivers list in the message
//		int iReceiverListEndLoc=s_Message.substr(4).find_first_of(";")+4;
//
//		//get all the receiver names
//		vector<string> * oReceivers = new vector<string>;
//		std::size_t iPrev = 4, iPos;
//		while ((iPos = s_Message.find_first_of(",", iPrev)) != std::string::npos)
//		{
//			if ( iPos > iPrev){
//				oReceivers->push_back(s_Message.substr(iPrev, iPos-iPrev));
//			}
//			iPrev = iPos+1;
//
//
//		}
//
//		//fetch the last name also
//		if (iPrev < iReceiverListEndLoc)
//		{
//			oReceivers->push_back(s_Message.substr(iPrev, iReceiverListEndLoc-iPrev));
//		}
//
//		oMessage=new Message(s_Message.substr(iReceiverListEndLoc+1,s_Message.length()-iReceiverListEndLoc),DIRECT,i_Sender,oReceivers,o_SenderSockAddr);
//
//	}
//	else if(oMsgType==LOGOUT)
//		{
//			LogDebug("MessageFactory.cpp: Logout Message from  %d",i_Sender);
//			oMessage=new Message("Logout",LOGOUT,i_Sender,NULL,o_SenderSockAddr);
//		}
//	else		//else this is an invalid message
//	{
//		LogDebug("MessageFactory.cpp: Error Message from  %d",i_Sender);
//		oMessage=new Message(s_Message,ERROR,i_Sender,NULL,o_SenderSockAddr);
//	}
//
//
//
//	return oMessage;
//
//}

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
	sMsg=p_UserRegistry->GetUser(pClient)->GetUserName();
	sMsg.append(" : ");

	vector<User*> *pTargetUsers = new vector<User*>();

	for(vector<string>::iterator it=pReceivers->begin();it!=pReceivers->end();++it)
	{
		//check whether the receiver exists
		if(!p_UserRegistry->IsUserExists((*it))){
			LogDebug("DeliveryController.cpp :Invalid recipient %s in the message from %d.",(*it).c_str(),pClient->GetSocket());

			string sReplyMsg("Invalid recipient "+(*it));
			//send an error message
			//p_StringMsgBuilder->CreateNotificationMessage(&sReplyMsg);

			//p_SocketOperator->WriteToSocket(o_Message->GetSenderSocket(),sReplyMsg,sReplyMsg.length());

			//return;
		}
		sMsg+=(*it);
		sMsg+=",";

		//set the target users
		pTargetUsers->push_back(p_UserRegistry->GetUser(*it));
	}
	//delete the final ,
	sMsg.erase(sMsg.length()-1);

	sMsg.append(" : ");
	sMsg.append(sMessage);
//	LogDebug("DeliveryController.cpp :Sending message %s.",sMsg.c_str());
//	LogDebug("DeliveryController.cpp :Message length %d.",sMsg.length());
	//p_StringMsgBuilder->CreateChatMessage(&sMsg);

	//call an internal function and build the encoded message
	string sEncodedMsg = CreateEncodedMessageString(DIRECT, sMsg);

	Message* pMsg = new Message(sEncodedMsg, sMsg, pReceivedServer, pClient, pTargetUsers);


	return pMsg;
	

	
}

//MessageFactory::MessageFactory()
//{
//	 this->c_MessageSeperator=';';
//}

Message* MessageFactory::CreateAuthStatusMessage(bool bAuthStatus,
		Server* pReceivedServer, Client* pClient)
{
	string sMessageContent;
	if(bAuthStatus){
		(sMessageContent)="success";
	}
	else{
		(sMessageContent)="failure";
	}

	string sEncodedMsg = CreateEncodedMessageString(AUTHENTICATION, sMessageContent);

	vector<User*> *pTargetUsers = new vector<User*>();
	pTargetUsers->push_back(p_UserRegistry->GetUser(pClient));

	Message* pMsg = new Message(sEncodedMsg, sMessageContent, pReceivedServer, pClient, pTargetUsers);

	return pMsg;


}

// |;|7+4+2+5|LIN;ishan|;|
std::string MessageFactory::CreateEncodedMessageString( MessageType eMessageType,string s_Message )
{
	//get the protocol string
	string sProtocol(GetTextForEnum(eMessageType));

	//get total message length
	int iMsgLength = GetMessageHeader().length()+GetMessageLengthSectionLength()+(sProtocol.length())+s_Message.length()+GetMessageFooter().length();
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
	sNotifMsg.append(s_Message);
	sNotifMsg.append(GetMessageFooter());
	return sNotifMsg;
}

MessageFactory::MessageFactory(UserRegistry* pUserRegistry)
{
	this->p_UserRegistry = pUserRegistry;
}
