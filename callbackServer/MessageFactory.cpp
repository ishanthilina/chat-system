#include "MessageFactory.h"


MessageType MessageFactory::getMessageType( string sMessage )
{
	if(sMessage.length()<2){
		return ERROR;
	}
	string sType = sMessage.substr(0,4);

	return GetEnumFromString(sType);



}


ChatMessage * MessageFactory::createChatMessage( string sMessage, Server* pReceivedServer, Client* pClient, list<string>* pReceivers )
{
	LogDebug("MessageFactory.cpp : Creating chat message out of : %s", sMessage.c_str());

	//set the message content (sender name + receiver names+ message)
	string sMsg;
	sMsg=p_UserRegistry->GetUser(pClient)->GetUserName();
	sMsg.append(" : ");

	list<User*> *pTargetUsers = new list<User*>();

	for(list<string>::iterator it=pReceivers->begin();it!=pReceivers->end();++it)
	{
		//check whether the receiver exists
		if(!p_UserRegistry->IsUserExists((*it))){
			LogDebug("MessageFactory.cpp :Invalid recipient %s in the message from %d.",(*it).c_str(),pClient->GetSocket());

			string sReplyMsg("Invalid recipient "+(*it));
			//send an error message

			Message* pMsg = new Message(CreateEncodedMessageString(NOTIFICATION,sReplyMsg));
			pClient->SendMessage(pMsg);

		}
		sMsg+=(*it);
		sMsg+=",";

		//set the target users
		User* pUser =p_UserRegistry->GetUser(*it);
		if (pUser != NULL)
		{
			pTargetUsers->push_back(pUser);
		}
		
	}
	//delete the final ,
	sMsg.erase(sMsg.length()-1);

	sMsg.append(" : ");
	sMsg.append(sMessage);

	//call an internal function and build the encoded message
	string sEncodedMsg = CreateEncodedMessageString(DIRECT, sMsg);

	ChatMessage* pMsg = new ChatMessage(sEncodedMsg, sMsg, pReceivedServer, pClient, pTargetUsers);


	return pMsg;
	

	
}


ChatMessage* MessageFactory::CreateAuthStatusMessage(bool bAuthStatus,
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

	list<User*> *pTargetUsers = new list<User*>();
	pTargetUsers->push_back(p_UserRegistry->GetUser(pClient));

	ChatMessage* pMsg = new ChatMessage(sEncodedMsg, sMessageContent, pReceivedServer, pClient, pTargetUsers);

	return pMsg;


}


std::string MessageFactory::CreateEncodedMessageString( MessageType eMessageType,string s_Message )
{
	//TODO - should not add headers and footers, they should be managed by the message class

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
	p_UserRegistry = pUserRegistry;
}
