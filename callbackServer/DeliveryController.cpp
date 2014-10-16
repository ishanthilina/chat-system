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
		LogDebug("DeliveryController.cpp : Login request from socket %d",o_Message->GetClient()->GetSocket());

		User* pUser = new User(o_Message->GetMessage(),o_Message->GetClient());
		int output=p_UserRegistry->AddUser(pUser);
		string sReplyMsg;
		Message* pReplyMsg;
		if(!output){	//if adding new client was successful
			LogDebug("DeliveryController.cpp : Authentication success for %s",pUser->GetUserName().c_str());
			//sReplyMsg=p_StringMsgBuilder->CreateAuthStatusMessage(true);
			pReplyMsg = p_MessageFactory->CreateAuthStatusMessage(true,o_Message->GetServer(),o_Message->GetClient());
		}
		else{
			LogDebug("DeliveryController.cpp : Authentication failed for %s",pUser->GetUserName().c_str());
			//sReplyMsg=p_StringMsgBuilder->CreateAuthStatusMessage(false);
			pReplyMsg = p_MessageFactory->CreateAuthStatusMessage(false,o_Message->GetServer(),o_Message->GetClient());
		}
		LogDebug("DeliveryController.cpp : Sending reply to %s - %s",pUser->GetUserName().c_str(),sReplyMsg.c_str());
		//p_SocketOperator->WriteToSocket(o_Message->GetSenderSocket(),sReplyMsg,sReplyMsg.length());
		output=pReplyMsg->SendMessage();


	}
	else if(o_Message->GetMessageType()==DIRECT)
	{
		LogDebug("DeliveryController.cpp : Chat message from socket %d",o_Message->GetClient()->GetSocket());

			//Authenticate the message
			/*Client * oClient;
			oClient=p_ClientRegistry->GetClient(o_Message->GetSenderSocket());
			if (oClient==NULL)
			{
				LogDebug("DeliveryController.cpp :Authentication failure for socket %d.",o_Message->GetSenderSocket());
				string sReplyMsg=p_StringMsgBuilder->CreateAuthStatusMessage(true);
				p_SocketOperator->WriteToSocket(o_Message->GetSenderSocket(),sReplyMsg,sReplyMsg.length());
				return;
			}*/

			//create the message using message factory

		//log event
		//p_Logger->LogEvent(oClient,sMsg);

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

