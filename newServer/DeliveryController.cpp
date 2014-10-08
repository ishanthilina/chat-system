/*
 * DeliveryController.cpp
 *
 *  Created on: Oct 8, 2014
 *      Author: ishan
 */

#include "DeliveryController.h"



void DeliveryController::processMessage(Message* o_Message)
{


	//login message
	if(o_Message->GetMessageType()==LOGIN)
	{
		cout<<"DeliveryController::login msg"<<endl;

		Client* oClient = new Client(o_Message->GetMessage(),o_Message->GetSenderSocket(),o_Message->GetSenderSockAddr());
		int output=p_ClientRegistry->AddClient(oClient);
		string sReplyMsg;
		//TODO - Create AUTH message and send
		if(!output){
			LogDebug("Authentication success for %s",oClient->GetUserName().c_str());
			sReplyMsg=p_StringMsgBuilder->CreateAuthStatusMessage(true);
		}
		else{
			LogDebug("Authentication failed for %s",oClient->GetUserName().c_str());
			sReplyMsg=p_StringMsgBuilder->CreateAuthStatusMessage(false);
		}
		printf("%s",sReplyMsg.c_str());
		p_SocketOperator->WriteToSocket(o_Message->GetSenderSocket(),sReplyMsg,sReplyMsg.length());


	}
	else if(o_Message->GetMessageType()==DIRECT)
	{
		cout<<"DeliveryController::PTP msg"<<endl;

			//Authenticate the message
			Client * oClient;
			oClient=p_ClientRegistry->GetClient(o_Message->GetSenderSocket());
			if (oClient==NULL)
			{
				LogDebug("Authentication failure for socket %d. Please re-login ",o_Message->GetSenderSocket());
				//TODO - send reply
				//o_Server->SendMessage("Authentication failure!. Please re-login.",o_Message->GetSenderSocket());
				return;
			}

			//cout<<"DeliveryController::direct msg"<<endl;

			//construct the message to be sent
			string sMsg;
			//cout<<oClient->GetSocket();  // SEGFAULT HERE
			sMsg=oClient->GetUserName();
			sMsg.append(" : ");

			vector<string> * oReceivers=o_Message->getReceivers();
			for(vector<string>::iterator it=oReceivers->begin();it!=oReceivers->end();++it)
			{
				//check whether the receiver exists
				if(!p_ClientRegistry->IsClientExists((*it))){
					LogDebug("Invalid recipient %s",(*it).c_str());
					//o_Server->SendMessage("Invalid recipient "+(*it),o_Message->GetSenderSocket());
					return;
				}
				sMsg+=(*it);
				sMsg+=",";
			}
			//delete the final ,
			sMsg.erase(sMsg.length()-1);

			sMsg.append(" : ");
			sMsg.append(o_Message->GetMessage());
			p_StringMsgBuilder->CreateChatMessage(&sMsg);

			//send the message to all the recipients
			Client * oClient1;
			for(vector<string>::iterator it=oReceivers->begin();it!=oReceivers->end();++it)
			{
				oClient1=p_ClientRegistry->GetClient(*it);
				if(oClient1!=NULL)
				{
					//p_SocketOperator->SendMessage(sMsg,oClient1->GetSocket());
					p_SocketOperator->WriteToSocket(oClient1->GetSocket(),sMsg,sMsg.length());
				}

			}

			p_Logger->LogEvent(oClient,sMsg);
			//cout<<sMsg<<endl;
			//cout<<"End"<<endl;

		}
}

DeliveryController::DeliveryController(ClientRegistry* pClientRegistry,
		SocketOperator* pSocketOperator)
{
	this->p_ClientRegistry = pClientRegistry;
	this->p_SocketOperator = pSocketOperator;
	this->p_Logger=new Logger();
	this->p_StringMsgBuilder = new StringMessageBuilder();
}

DeliveryController::~DeliveryController() {
	delete p_Logger;
	delete p_StringMsgBuilder;
}

