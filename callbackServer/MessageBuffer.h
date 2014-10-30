/*
 * MessageBuffer.h
 *
 *  Created on: Oct 8, 2014
 *      Author: ishan
 */

#ifndef _MESSAGEBUFFER_HEADER_
#define _MESSAGEBUFFER_HEADER_

#include <netinet/in.h>	//sockaddr_in

#include <string>
#include <map>
#include <cstring>

#include "MessageFactory.h"
#include "Message.h"
#include "DeliveryController.h"

using namespace std;

typedef std::map<Client*, Message*> TPClientMsgMap;

class MessageBuffer {
public:
	MessageBuffer(DeliveryController * pDeliveryController);
	virtual ~MessageBuffer();
	void CreateMessage(Server* pServer, Client* pClient,string sNewMessage);
private:
	TPClientMsgMap* p_BufferredMessages;
	DeliveryController * p_DeliveryController;

};

#endif /* _MESSAGEBUFFER_HEADER_ */
