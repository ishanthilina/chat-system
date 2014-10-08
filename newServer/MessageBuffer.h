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
#include <vector>

using namespace std;

class MessageBuffer {
public:
	MessageBuffer();
	virtual ~MessageBuffer();
	void CreateMessage(int iSocketDescriptor,string sNewMessage,sockaddr_in oAddress);
};

#endif /* MESSAGEBUFFER_H_ */
