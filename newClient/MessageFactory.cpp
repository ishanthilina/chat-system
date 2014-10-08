/*
 * MessageFactory.cpp
 *
 *  Created on: Oct 6, 2014
 *      Author: ishan
 */

#include "MessageFactory.h"

MessageFactory::MessageFactory(MessageProcessor * oMessageProcessor) {
	this->i_CurrentMsgLength = 0;
	this->s_CurrentMessage="";
	this->o_MessageProcessor=oMessageProcessor;

}

void MessageFactory::CreateMessage(string sNewMessage)
{
	// |;|7+4+2+5|LIN;ishan|;|

	if(this->i_CurrentMsgLength == 0)	//this is the begining of a new message
	{
		//check for the beginning signature of the message
		if(sNewMessage.substr(0,3).compare("|;|")!=0){
			this->i_CurrentMsgLength = 0;
			this->s_CurrentMessage="";
			return;
		}

		//get the length of the total message
		const char* pzMsgLength=sNewMessage.substr(3,2).c_str();
		i_CurrentMsgLength=atoi(pzMsgLength);

	}

	//add to the buffer
	this->s_CurrentMessage.append(sNewMessage);

	//if the complete message is received
	if (this->s_CurrentMessage.length() == i_CurrentMsgLength)
	{
		o_MessageProcessor->ProcessServerInput(this->s_CurrentMessage.substr(6,(this->s_CurrentMessage.length()-4) ));
		this->i_CurrentMsgLength = 0;
		this->s_CurrentMessage="";
		return;

	}
	else if(this->s_CurrentMessage.length() > i_CurrentMsgLength)	//if the message size has been exceeded
	{
		//TODO - show error
		cout<<"Invalid incoming message - Exceeds defined length -"<<sNewMessage<<"  "<<s_CurrentMessage.length()<<"---"<<i_CurrentMsgLength<<endl;
	}

}

MessageFactory::~MessageFactory() {
	// TODO Auto-generated destructor stub
}

