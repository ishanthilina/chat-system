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

Message* MessageFactory::createChatMessage(string sMessage,
		Server* pReceivedServer, Client* pClient, vector<string>* pReceivers) {
}

MessageFactory::MessageFactory()
{
	 this->c_MessageSeperator=';';
}

Message* MessageFactory::CreateAuthStatusMessage(bool bAuthStatus,
		Server* pReceivedServer, Client* pClient) {
}
