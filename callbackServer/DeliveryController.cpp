/*
 * DeliveryController.cpp
 *
 *  Created on: Oct 8, 2014
 *      Author: ishan
 */

#include "DeliveryController.h"



void DeliveryController::processMessage(Message* o_Message)
{

	//LogDebug("ss %d", o_Message->GetMessageType());

	//login message
	if(o_Message->GetMessageType()==LOGIN)
	{
		LogDebug("DeliveryController.cpp : Login request from socket %d",o_Message->GetClient()->GetSocket());

		User* pUser = new User(o_Message->GetMessage(),o_Message->GetClient());
		int output=p_UserRegistry->AddUser(pUser);
		//std::string sReplyMsg;
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
		LogDebug("DeliveryController.cpp : Sending reply to %s - %s",pUser->GetUserName().c_str(),pReplyMsg->GetEncodedMessage().c_str());
		//p_SocketOperator->WriteToSocket(o_Message->GetSenderSocket(),sReplyMsg,sReplyMsg.length());
		output=pReplyMsg->sendMessageToClient();


	}
	else if(o_Message->GetMessageType()==DIRECT)
	{
		LogDebug("DeliveryController.cpp : Chat message from socket %d",o_Message->GetClient()->GetSocket());

			//Authenticate the message
			User * pUser;
			pUser=p_UserRegistry->GetUser(o_Message->GetClient());
			if (pUser==NULL)
			{
				LogDebug("DeliveryController.cpp :Authentication failure for socket %d.",o_Message->GetClient()->GetSocket());
				Message* pReplyMsg;
				pReplyMsg = p_MessageFactory->CreateAuthStatusMessage(false,o_Message->GetServer(),o_Message->GetClient());
				pReplyMsg->sendMessageToClient();
				delete pReplyMsg;
				return;
			}

			//create the message using message factory
			Message* pReplyMsg;

			pReplyMsg = this->p_MessageFactory->createChatMessage(o_Message->GetMessage(),o_Message->GetServer(), o_Message->GetClient(), o_Message->GetReceivers());
			pReplyMsg->SendMessageToReceivers();


		//log event
		//p_Logger->LogEvent(oClient,sMsg);

		}
}

DeliveryController::DeliveryController(UserRegistry* pUserRegistry,
		MessageFactory* pMessageFactory)
{
	this->p_UserRegistry = pUserRegistry;
	this-> p_MessageFactory = pMessageFactory;

}

DeliveryController::~DeliveryController() {
	//delete p_Logger;
	//delete p_StringMsgBuilder;
}

