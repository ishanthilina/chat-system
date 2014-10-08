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
			//cout<<"DeliveryController::login msg"<<endl;

			Client* oClient = new Client(o_Message->GetMessage(),o_Message->GetSenderSocket(),o_Message->GetSenderSockAddr());
			int output=p_ClientRegistry->AddClient(oClient);
			string sReplyMsg;
			//TODO - Create AUTH message and send
			if(output){

				sReplyMsg=p_StringMsgBuilder->CreateAuthStatusMessage(false);
			}
			else{
				sReplyMsg=p_StringMsgBuilder->CreateAuthStatusMessage(true);
			}
			p_SocketOperator->WriteToSocket(o_Message->GetSenderSocket(),o_Message->GetMessage(),o_Message->GetMessage().length());


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

