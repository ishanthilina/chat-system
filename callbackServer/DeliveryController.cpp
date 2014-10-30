/*
 * DeliveryController.cpp
 *
 *  Created on: Oct 8, 2014
 *      Author: ishan
 */

#include "DeliveryController.h"



void DeliveryController::processMessage(Message* pMessage)
{
	//login message
	if(pMessage->GetMessageType()==LOGIN)
	{
		LogDebug("DeliveryController.cpp : Login request from socket %d",pMessage->GetClient()->GetSocket());

		User* pUser = new User(pMessage->GetMessage(),pMessage->GetClient());
		int output=p_UserRegistry->AddUser(pUser);

		Message* pReplyMsg;
		if(!output){	//if adding new client was successful
			LogDebug("DeliveryController.cpp : Authentication success for %s",pUser->GetUserName().c_str());
			pReplyMsg = p_MessageFactory->CreateAuthStatusMessage(true,pMessage->GetServer(),pMessage->GetClient());
		}
		else{
			LogDebug("DeliveryController.cpp : Authentication failed for %s",pUser->GetUserName().c_str());
			pReplyMsg = p_MessageFactory->CreateAuthStatusMessage(false,pMessage->GetServer(),pMessage->GetClient());
		}
		LogDebug("DeliveryController.cpp : Sending reply to %s - %s",pUser->GetUserName().c_str(),pReplyMsg->GetEncodedMessage().c_str());
		output=pReplyMsg->sendMessageToClient();


	}
	else if(pMessage->GetMessageType()==DIRECT)
	{
		LogDebug("DeliveryController.cpp : Chat message from socket %d",pMessage->GetClient()->GetSocket());

			//Authenticate the message
			User * pUser;
			pUser = p_UserRegistry->GetUser(pMessage->GetClient());
			if (pUser == NULL)
			{
				LogDebug("DeliveryController.cpp :Authentication failure for socket %d.",pMessage->GetClient()->GetSocket());
				Message* pReplyMsg;
				pReplyMsg = p_MessageFactory->CreateAuthStatusMessage(false,pMessage->GetServer(),pMessage->GetClient());
				pReplyMsg->sendMessageToClient();
				delete pReplyMsg;
				return;
			}

			

			//create the message using message factory
			Message* pReplyMsg;

			pReplyMsg = this->p_MessageFactory->createChatMessage(pMessage->GetMessage(),pMessage->GetServer(), pMessage->GetClient(), pMessage->GetReceivers());
			pReplyMsg->SendMessageToReceivers();


		//log event
		p_Logger->LogEvent(pUser,pReplyMsg->GetEncodedMessage());

		}
}

DeliveryController::DeliveryController(UserRegistry* pUserRegistry,
		MessageFactory* pMessageFactory)
{
	this->p_UserRegistry = pUserRegistry;//TODO: remove this
	this-> p_MessageFactory = pMessageFactory;
	this->p_Logger = new Logger();

}

DeliveryController::~DeliveryController() {
	delete p_Logger;

}

