/*
 * MessageBuffer.cpp
 *
 *  Created on: Oct 8, 2014
 *      Author: ishan
 */

#include "MessageBuffer.h"

MessageBuffer::MessageBuffer(DeliveryController * pDeliveryController) {
	// TODO Auto-generated constructor stub
	p_BufferredMessages = new TintBMMap();
	p_MsgFactory = new MessageFactory();

	p_DeliveryController = pDeliveryController;


}

MessageBuffer::~MessageBuffer() {
	delete p_MsgFactory;
	delete p_BufferredMessages;
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
			//create message out of it
			string sMsg=oBufferedMsg->GetFullMessage();
			Message * pMessage = p_MsgFactory->createMessage(iSocketDescriptor,
					sMsg.substr(6,(sMsg.length()-4) ),
					oAddress);

			p_DeliveryController->processMessage(pMessage);
			//remove the message from the map
			p_BufferredMessages->erase(it);

			delete pMessage;
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
