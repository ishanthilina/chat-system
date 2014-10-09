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
		LogDebug("DeliveryController.cpp : Login request from socket %d",o_Message->GetSenderSocket());

		Client* oClient = new Client(o_Message->GetMessage(),o_Message->GetSenderSocket(),o_Message->GetSenderSockAddr());
		int output=p_ClientRegistry->AddClient(oClient);
		string sReplyMsg;
		if(!output){	//if adding new client was successful
			LogDebug("DeliveryController.cpp : Authentication success for %s",oClient->GetUserName().c_str());
			sReplyMsg=p_StringMsgBuilder->CreateAuthStatusMessage(true);
		}
		else{
			LogDebug("DeliveryController.cpp : Authentication failed for %s",oClient->GetUserName().c_str());
			sReplyMsg=p_StringMsgBuilder->CreateAuthStatusMessage(false);
		}
		LogDebug("DeliveryController.cpp : Sending reply to %s - %s",oClient->GetUserName().c_str(),sReplyMsg.c_str());
		p_SocketOperator->WriteToSocket(o_Message->GetSenderSocket(),sReplyMsg,sReplyMsg.length());


	}
	else if(o_Message->GetMessageType()==DIRECT)
	{
		LogDebug("DeliveryController.cpp : Chat message from socket %d",o_Message->GetSenderSocket());

			//Authenticate the message
			Client * oClient;
			oClient=p_ClientRegistry->GetClient(o_Message->GetSenderSocket());
			if (oClient==NULL)
			{
				LogDebug("DeliveryController.cpp :Authentication failure for socket %d.",o_Message->GetSenderSocket());
				string sReplyMsg=p_StringMsgBuilder->CreateAuthStatusMessage(true);
				p_SocketOperator->WriteToSocket(o_Message->GetSenderSocket(),sReplyMsg,sReplyMsg.length());
				return;
			}

			//construct the message to be sent
			string sMsg;
			sMsg=oClient->GetUserName();
			sMsg.append(" : ");

			vector<string> * oReceivers=o_Message->getReceivers();
			for(vector<string>::iterator it=oReceivers->begin();it!=oReceivers->end();++it)
			{
				//check whether the receiver exists
				if(!p_ClientRegistry->IsClientExists((*it))){
					LogDebug("DeliveryController.cpp :Invalid recipient %s in the message from %s.",(*it).c_str(),oClient->GetUserName().c_str());
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

			LogDebug("DeliveryController.cpp :Sending message %s.",sMsg.c_str());
			LogDebug("DeliveryController.cpp :Message length %d.",sMsg.length());

			//send the message to all the recipients
			Client * oClient1;
			for(vector<string>::iterator it=oReceivers->begin();it!=oReceivers->end();++it)
			{
				oClient1=p_ClientRegistry->GetClient(*it);
				if(oClient1!=NULL)
				{
					LogDebug("DeliveryController.cpp :sending message to %s.",oClient1->GetUserName().c_str());
					p_SocketOperator->WriteToSocket(oClient1->GetSocket(),sMsg,sMsg.length());
				}

			}

			p_Logger->LogEvent(oClient,sMsg);

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

