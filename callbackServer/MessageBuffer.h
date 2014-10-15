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
#include <cstring>

//#include "BufferredMessage.h"
#include "MessageFactory.h"
#include "Message.h"
#include "DeliveryController.h"

using namespace std;

typedef std::map<Client*, Message*> TPClientMsgMap;

class MessageBuffer {
public:
	MessageBuffer(DeliveryController * pDeliveryController, MessageFactory* pMessageFactory);
	virtual ~MessageBuffer();
	void CreateMessage(Server* pServer, Client* pClient,string sNewMessage);
private:
	TPClientMsgMap* p_BufferredMessages;
	MessageFactory * p_MsgFactory;
	DeliveryController * p_DeliveryController;

};

#endif /* MESSAGEBUFFER_H_ */
