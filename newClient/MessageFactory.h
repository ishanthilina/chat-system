/*
 * MessageFactory.h
 *
 *  Created on: Oct 6, 2014
 *      Author: ishan
 */

#ifndef _MESSAGE_FACTORY_HEADER_
#define _MESSAGE_FACTORY_HEADER_

#include <string>
#include <stdlib.h>     /* atoi */
#include "MessageProcessor.h"
#include <iostream>

using namespace std;

class MessageFactory {
public:
	MessageFactory(MessageProcessor * pMessageProcessor);
	void CreateMessage(string sNewMessage);
	virtual ~MessageFactory();
private:
	int i_CurrentMsgLength;
	string s_CurrentMessage;
	MessageProcessor * p_MessageProcessor;
};

#endif /* _MESSAGE_FACTORY_HEADER_ */

