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

using namespace std;

class MessageFactory {
public:
	MessageFactory();
	void CreateMessage(string sNewMessage);
	virtual ~MessageFactory();
private:
	int i_CurrentMsgLength;
	string s_CurrentMessage;
};

#endif /* MESSAGEFACTORY_H_ */

// |;|7+4+2+5|LIN;ishan|;|
