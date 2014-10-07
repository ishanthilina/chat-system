/*
 * MessageFactory.h
 *
 *  Created on: Oct 6, 2014
 *      Author: ishan
 */

#ifndef MESSAGEFACTORY_H_
#define MESSAGEFACTORY_H_

#include <string>
#include <stdlib.h>     /* atoi */
#include "MessageProcessor.h"
#include <iostream>

using namespace std;

class MessageFactory {
public:
	MessageFactory(MessageProcessor * oMessageProcessor);
	void CreateMessage(string sNewMessage);
	virtual ~MessageFactory();
private:
	int i_CurrentMsgLength;
	string s_CurrentMessage;
	MessageProcessor * o_MessageProcessor;
};

#endif /* MESSAGEFACTORY_H_ */

// |;|7+4+2+5|LIN;ishan|;|
