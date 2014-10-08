/*
 * BufferredMessage.h
 *
 *  Created on: Oct 8, 2014
 *      Author: ishan
 */

#ifndef BUFFERREDMESSAGE_H_
#define BUFFERREDMESSAGE_H_

#include <string>
#include <stdlib.h>     /* atoi */
using namespace std;

class BufferredMessage {
public:
	BufferredMessage(string sMessage);
	bool IsMessageComplete();
	void FillMessage(string sMessage);
	bool IsValidMessage();
	string GetFullMessage();
	virtual ~BufferredMessage();
private:
	int i_MsgLength;
	string s_Message;
	bool b_ValidMessage;
};

#endif /* BUFFERREDMESSAGE_H_ */
