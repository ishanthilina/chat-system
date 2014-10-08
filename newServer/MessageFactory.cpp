#include "MessageFactory.h"


Message * MessageFactory::createMessage( int i_Sender, string s_Message, sockaddr_in o_SenderSockAddr)
{
	LogDebug("MessageFactory.cpp: Generating message for :: %s",s_Message.c_str());
	//cout<<"MessageFactory::createMessage"<<endl;
	MessageType oMsgType=getMessageType(s_Message);

	Message * oMessage;
	//if this is a login message
	if(oMsgType==LOGIN)
	{
		cout<<"MessageFactory::login msg"<<endl;
		oMessage=new Message(s_Message.substr(4),LOGIN,i_Sender,NULL,o_SenderSockAddr);
	}
	else if(oMsgType==DIRECT)
	{
		cout<<"MessageFactory::direct msg"<<endl;
		//find the ending location of the receivers list in the message
		int iReceiverListEndLoc=s_Message.substr(4).find_first_of(";")+4;

		//get all the receiver names
		vector<string> * oReceivers = new vector<string>;
		std::size_t iPrev = 4, iPos;
		while ((iPos = s_Message.find_first_of(",", iPrev)) != std::string::npos)
		{
			if ( iPos > iPrev){

				//cout<<s_Message.substr(iPrev, iPos-iPrev)<<endl;
				oReceivers->push_back(s_Message.substr(iPrev, iPos-iPrev));
			}
			iPrev = iPos+1;
			

		}

		//fetch the last name also
		if (iPrev < iReceiverListEndLoc)
		{
			
			//cout<<s_Message.substr(iPrev, iReceiverListEndLoc-iPrev)<<endl;
			oReceivers->push_back(s_Message.substr(iPrev, iReceiverListEndLoc-iPrev));
		}

		oMessage=new Message(s_Message.substr(iReceiverListEndLoc+1,s_Message.length()-iReceiverListEndLoc),DIRECT,i_Sender,oReceivers,o_SenderSockAddr);
		
	}
	else if(oMsgType==LOGOUT)
		{
		oMessage=new Message("Logout",LOGOUT,i_Sender,NULL,o_SenderSockAddr);
		}
	else		//else this is an invalid message
	{	
		cout<<"MessageFactory::ERROR msg"<<endl;
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

MessageFactory::MessageFactory()
{
	 this->c_MessageSeperator=';';
}
