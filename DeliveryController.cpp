#include "DeliveryController.h"

DeliveryController::DeliveryController( Logger * o_Logger)
{
	this->o_Logger = o_Logger;
	
}

int DeliveryController::processMessage( Message * o_Message )
{
	cout<<"Processing message: "<< o_Message->GetMessage()<<endl;

	//login message
	if(o_Message->GetMessageType()==LOGIN)
	{
		//cout<<"DeliveryController::login msg"<<endl;

		Client* oClient = new Client(o_Message->GetMessage(),o_Message->GetSenderSocket(),o_Message->GetSenderSockAddr());
		int output=o_Server->AddClient(oClient);
		string sReplyMsg;
		if(output){
			sReplyMsg="Login Failed!!";
		}
		else{
			sReplyMsg="Login Success!";
		}
		o_Server->SendMessage(sReplyMsg,o_Message->GetSenderSocket());

	}
	else if(o_Message->GetMessageType()==DIRECT){

		//Authenticate the message
		Client * oClient;
		int status=o_Server->GetClient(oClient,o_Message->GetSenderSocket());
		if (status)
		{
			o_Server->SendMessage("Authentication failure!. Please re-login.",o_Message->GetSenderSocket());
			return 1;
		}

		cout<<"DeliveryController::direct msg"<<endl;

		//construct the message to be sent
		string sMsg;
		cout<<oClient->GetSocket();  // SEGFAULT HERE
		sMsg=oClient->GetUserName();
		sMsg.append(" : ");

		vector<string> * oReceivers=o_Message->getReceivers();
		for(vector<string>::iterator it=oReceivers->begin();it!=oReceivers->end();++it)
		{
			//check whether the receiver exists
			if(!o_Server->IsClientExists((*it))){
				o_Server->SendMessage("Invalid recipient "+(*it),o_Message->GetSenderSocket());
				return 1;
			}
			sMsg+=(*it);
			sMsg+=",";
		}
		//delete the final ,
		sMsg.erase(sMsg.length()-1);
		
		sMsg.append(" : ");
		sMsg.append(o_Message->GetMessage());



		cout<<sMsg<<endl;
		cout<<"End"<<endl;

	}

	return 0;

}

void DeliveryController::setServer(Server * o_Server)
{
	this->o_Server = o_Server;
}
