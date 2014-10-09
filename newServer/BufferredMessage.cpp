/*
 * BufferredMessage.cpp
 *
 *  Created on: Oct 8, 2014
 *      Author: ishan
 */

#include "BufferredMessage.h"

BufferredMessage::BufferredMessage(string sMessage)
{
	//check for the beginning signature of the message
	if(sMessage.substr(0,3).compare("|;|")!=0){
		this->b_ValidMessage=false;
		return;
	}

	//get the length of the total message
	const char* pzMsgLength=sMessage.substr(3,7).c_str();
	i_MsgLength=atoi(pzMsgLength);

	this->s_Message=sMessage;
	this->b_ValidMessage=true;
}

bool BufferredMessage::IsMessageComplete()
{
	if(this->s_Message.length()==this->i_MsgLength)
	{
		return true;
	}

	return false;
}

void BufferredMessage::FillMessage(string sMessage)
{
	if(!IsMessageComplete() && IsValidMessage()){
		this->s_Message.append(sMessage);
	}


}

bool BufferredMessage::IsValidMessage() {

	if(this->s_Message.length()>this->i_MsgLength){
		this->b_ValidMessage=false;
	}

	return b_ValidMessage;
}

string BufferredMessage::GetFullMessage()
{
	return s_Message;
}

BufferredMessage::~BufferredMessage()
{
	// TODO Auto-generated destructor stub
}

