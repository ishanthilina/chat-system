/*
 * MessageFactory.cpp
 *
 *  Created on: Oct 6, 2014
 *      Author: ishan
 */

#include "MessageFactory.h"

MessageFactory::MessageFactory() {
	this->i_CurrentMsgLength = 0;
	this->s_CurrentMessage="";

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
		char* pzMsgLength=sNewMessage.substr(3,1).c_str();
		int iMsgLength=atoi(pzMsgLength);

	}
}

MessageFactory::~MessageFactory() {
	// TODO Auto-generated destructor stub
}

