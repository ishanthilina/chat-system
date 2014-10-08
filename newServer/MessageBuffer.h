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

using namespace std;

typedef std::map<int, BufferredMessage*> TintBMMap;

class MessageBuffer {
public:
	MessageBuffer();
	virtual ~MessageBuffer();
	void CreateMessage(int iSocketDescriptor,string sNewMessage,sockaddr_in oAddress);
private:
	TintBMMap* p_BufferredMessages;
	MessageFactory * p_MsgFactory;

};

#endif /* MESSAGEBUFFER_H_ */
