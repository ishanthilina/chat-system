#include "MessageFactory.h"


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
	LogDebug("MessageFactory.cpp : Creating chat message out of : %s", sMessage.c_str());

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

			pClient->SendMessage(sReplyMsg);

			//break;
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

	Message* pMsg = new Message(sEncodedMsg, sMsg, pReceivedServer, pClient, pTargetUsers);


	return pMsg;
	

	
}


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
