/*
 * MessageBuffer.cpp
 *
 *  Created on: Oct 8, 2014
 *      Author: ishan
 */

#include "MessageBuffer.h"

MessageBuffer::MessageBuffer(DeliveryController * pDeliveryController) {
	p_BufferredMessages = new TPClientMsgMap();
	//p_MsgFactory = pMessageFactory;

	p_DeliveryController = pDeliveryController;


}

MessageBuffer::~MessageBuffer() {
	//delete p_MsgFactory;
	delete p_BufferredMessages;
}

//|;|18|LIN;ishan|;|
//|;|21|PTP;ishan;qq|;|

//void MessageBuffer::CreateMessage(int iSocketDescriptor, string sNewMessage,
//		sockaddr_in oAddress)
//{
//
//	LogDebug("MessageBuffer.cpp : Socket Descriptor %d sent - %s",iSocketDescriptor,sNewMessage.c_str());
//
//	//remove any null characters or new lines at the end of the string
//	if(sNewMessage.compare(sNewMessage.length()-1,1,"\n") ==0)
//	{
//		sNewMessage=sNewMessage.substr(0,sNewMessage.size()-1);
//	}
//	if(sNewMessage.compare(sNewMessage.length()-1,1,"\r") ==0)
//	{
//		sNewMessage=sNewMessage.substr(0,sNewMessage.size()-1);
//	}
//
//
//	//check if a message is already being built for this socket
//	std::map<int, BufferredMessage*>::iterator it;
//	it=p_BufferredMessages->find(iSocketDescriptor);
//	if(it != p_BufferredMessages->end())
//	{
//		//append to the current message
//		BufferredMessage * oBufferedMsg=(*p_BufferredMessages)[iSocketDescriptor];
//		oBufferedMsg->FillMessage(sNewMessage);
//
//		//if the message is complete now
//		if(oBufferedMsg->IsMessageComplete())
//		{
//			//create message out of it
//			string sMsg=oBufferedMsg->GetFullMessage();
//			Message * pMessage = p_MsgFactory->createMessage(iSocketDescriptor,
//					sMsg.substr(GetTotalHeaderLength(),(sMsg.length()-(GetTotalHeaderLength()+GetTotalFooterLength())) ),
//					oAddress);
//
//			p_DeliveryController->processMessage(pMessage);
//			//remove the message from the map
//			p_BufferredMessages->erase(it);
//
//			delete pMessage;
//			delete oBufferedMsg;
//			return;
//
//		}
//
//		else if(!oBufferedMsg->IsValidMessage())
//		{
//			//TODO - shouldn't we report this error?
//
//			//remove the message from the map
//			p_BufferredMessages->erase(it);
//
//			delete oBufferedMsg;
//			return;
//
//		}
//	}
//
//	else	//if a message is not already being built
//	{
//		BufferredMessage * oBufferedMsg = new BufferredMessage(sNewMessage);
//
//		//only do anything if this is a valid message
//		if(oBufferedMsg->IsValidMessage())
//		{
//			//check if the message is completely built
//			if(oBufferedMsg->IsMessageComplete())
//			{
//				string sMsg=oBufferedMsg->GetFullMessage();
//				Message * pMessage = p_MsgFactory->createMessage(iSocketDescriptor,
//						sMsg.substr(GetTotalHeaderLength(),(sMsg.length()-(GetTotalHeaderLength()+GetTotalFooterLength())) ),
//						oAddress);
//
//				p_DeliveryController->processMessage(pMessage);
//				delete oBufferedMsg;
//				delete pMessage;
//				return;
//			}
//
//			p_BufferredMessages->insert(pair<int, BufferredMessage*>(iSocketDescriptor,oBufferedMsg));
//		}
//		else	//if invalid message
//		{
//			delete oBufferedMsg;
//		}
//
//
//	}
//
//}

void MessageBuffer::CreateMessage(Server* pServer, Client* pClient,
		string sNewMessage) {


	LogDebug("MessageBuffer.cpp : New Create Message request.");

	//remove any null characters or new lines at the end of the string
	if(sNewMessage.compare(sNewMessage.length()-1,1,"\n") ==0)
	{
		sNewMessage=sNewMessage.substr(0,sNewMessage.size()-1);
	}
	if(sNewMessage.compare(sNewMessage.length()-1,1,"\r") ==0)
	{
		sNewMessage=sNewMessage.substr(0,sNewMessage.size()-1);
	}

	//check if a message is already being built for this client
	std::map<Client*, Message*>::iterator it;
	it=p_BufferredMessages->find(pClient);
	if(it != p_BufferredMessages->end())
	{
		//append to the current message
		Message * oBufferedMsg=(*p_BufferredMessages)[pClient];
		oBufferedMsg->FillMessage(sNewMessage);

		//if the message is complete now
		if(oBufferedMsg->IsMessageComplete())
		{
			//create message out of it
			//				string sMsg=oBufferedMsg->GetFullMessage();
			//				Message * pMessage = p_MsgFactory->createMessage(iSocketDescriptor,
			//						sMsg.substr(GetTotalHeaderLength(),(sMsg.length()-(GetTotalHeaderLength()+GetTotalFooterLength())) ),
			//						oAddress);

			p_DeliveryController->processMessage(oBufferedMsg);
			//remove the message from the map
			p_BufferredMessages->erase(it);

			//delete pMessage;
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
		LogDebug("MessageBuffer.cpp : Creating new message.");

		Message * oBufferedMsg = new Message(sNewMessage, pServer, pClient);

		//only do anything if this is a valid message
		if(oBufferedMsg->IsValidMessage())
		{
			LogDebug("MessageBuffer.cpp : Created message status : Valid");
			//check if the message is completely built
			if(oBufferedMsg->IsMessageComplete())
			{
				LogDebug("MessageBuffer.cpp : Created message status : Complete.");
//				string sMsg=oBufferedMsg->GetFullMessage();
//				Message * pMessage = p_MsgFactory->createMessage(iSocketDescriptor,
//						sMsg.substr(GetTotalHeaderLength(),(sMsg.length()-(GetTotalHeaderLength()+GetTotalFooterLength())) ),
//						oAddress);

				p_DeliveryController->processMessage(oBufferedMsg);
				delete oBufferedMsg;
//				delete pMessage;
				return;
			}

			p_BufferredMessages->insert(pair<Client*, Message*>(pClient,oBufferedMsg));
		}
		else	//if invalid message
		{
			LogDebug("MessageBuffer.cpp : Created message status : Invalid");
			delete oBufferedMsg;
		}


	}

}
