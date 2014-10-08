/*
 * MessageBuffer.cpp
 *
 *  Created on: Oct 8, 2014
 *      Author: ishan
 */

#include "MessageBuffer.h"

MessageBuffer::MessageBuffer() {
	// TODO Auto-generated constructor stub
	TintBMMap* p_BufferredMessages = new TintBMMap();
		MessageFactory * p_MsgFactory;

}

MessageBuffer::~MessageBuffer() {
	// TODO Auto-generated destructor stub
}

void MessageBuffer::CreateMessage(int iSocketDescriptor, string sNewMessage,
		sockaddr_in oAddress)
{

	//check if a message is already being built for this socket
	std::map<int, BufferredMessage*>::iterator it;
	it=p_BufferredMessages->find(iSocketDescriptor);
	if(it != p_BufferredMessages->end())
	{
		//append to the current message
		BufferredMessage * oBufferedMsg=(*p_BufferredMessages)[iSocketDescriptor];
		oBufferedMsg->FillMessage(sNewMessage);

		//if the message is complete now
		if(oBufferedMsg->IsMessageComplete())
		{
			//TODO - Call the message processor

			//remove the message from the map
			p_BufferredMessages->erase(it);

			delete oBufferedMsg;
			return;

		}

		else if(!oBufferedMsg->IsValidMessage())
		{
			//TODO - shouldn't we report this error?

			//remove the message from the map
			p_BufferredMessages->erase(it);

			delete oBufferedMsg;
			return;

		}
	}

	else	//if a message is not already being built
	{
		BufferredMessage * oBufferedMsg = new BufferredMessage(sNewMessage);
		p_BufferredMessages->insert(pair<int, BufferredMessage*>(iSocketDescriptor,oBufferedMsg));
	}

}
