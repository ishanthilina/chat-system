/*
 * MessageFactory.cpp
 *
 *  Created on: Oct 6, 2014
 *      Author: ishan
 */

#include "MessageFactory.h"

MessageFactory::MessageFactory(MessageProcessor * pMessageProcessor) 
{
	this->i_CurrentMsgLength = 0;
	this->s_CurrentMessage="";
	this->p_MessageProcessor=pMessageProcessor;

}

void MessageFactory::CreateMessage(string sNewMessage)
{

	LogDebug("MessageFactory.cpp - New Input : %s",sNewMessage.c_str());

	if(this->i_CurrentMsgLength == 0)	//this is the beginning of a new message
	{
		//check for the beginning signature of the message
		if(sNewMessage.substr(0,3).compare("|;|")!=0)
		{
			this->i_CurrentMsgLength = 0;
			this->s_CurrentMessage="";
			return;
		}

		//get the length of the total message
		const char* pzMsgLength=sNewMessage.substr(3,7).c_str();	
		i_CurrentMsgLength=atoi(pzMsgLength);
		

		LogDebug("MessageFactory.cpp - Creating New Message");

	}

	//add to the buffer
	this->s_CurrentMessage.append(sNewMessage);

	//if the complete message is received
	if (this->s_CurrentMessage.length() == i_CurrentMsgLength)
	{
		LogDebug("MessageFactory.cpp - Message Complete - %s",this->s_CurrentMessage.c_str());
		p_MessageProcessor->ProcessServerInput(this->s_CurrentMessage.substr(GetTotalHeaderLength(),(this->s_CurrentMessage.length()-(GetTotalHeaderLength()+GetTotalFooterLength())) ));
		this->i_CurrentMsgLength = 0;
		this->s_CurrentMessage="";
		return;

	}
	else if(this->s_CurrentMessage.length() > i_CurrentMsgLength)	//if the message size has been exceeded
	{
		LogDebug("MessageFactory.cpp - Invalid incoming message - Exceeds defined length . Expected: - %d . Current - %d",i_CurrentMsgLength,this->s_CurrentMessage.length());
		this->i_CurrentMsgLength = 0;
		this->s_CurrentMessage="";
		return;
	}

}

MessageFactory::~MessageFactory() 
{
}

