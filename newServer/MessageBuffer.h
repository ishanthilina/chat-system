/*
 * MessageBuffer.h
 *
 *  Created on: Oct 8, 2014
 *      Author: ishan
 */

#ifndef MESSAGEBUFFER_H_
#define MESSAGEBUFFER_H_

#include <netinet/in.h>	//sockaddr_in

#include <string>
#include <map>

#include "BufferredMessage.h"
#include "MessageFactory.h"
#include "Message.h"
#include "DeliveryController.h"

using namespace std;

typedef std::map<int, BufferredMessage*> TintBMMap;

class MessageBuffer {
public:
	MessageBuffer(DeliveryController * pDeliveryController);
	virtual ~MessageBuffer();
	void CreateMessage(int iSocketDescriptor,string sNewMessage,sockaddr_in oAddress);
private:
	TintBMMap* p_BufferredMessages;
	MessageFactory * p_MsgFactory;
	DeliveryController * p_DeliveryController;

};

#endif /* MESSAGEBUFFER_H_ */
