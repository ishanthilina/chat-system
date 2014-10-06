/*
 * EventListener.h
 *
 *  Created on: Oct 5, 2014
 *      Author: ishan
 */

#ifndef EVENTLISTENER_H_
#define EVENTLISTENER_H_

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <netdb.h>
#include <iostream>

#include <sys/time.h> //FD_SET, FD_ISSET, FD_ZERO macros
#include <errno.h>
#include <string>

#include "SocketOperator.h"
#include "MessageProcessor.h"

class EventListener {
public:
	EventListener(int sockfd, SocketOperator * oNetSockOperator, SocketOperator * oTerminalSocketOperator,MessageProcessor * oMsgProcessor);
	int Listen();
	virtual ~EventListener();
private:
	int sockfd;
	SocketOperator * o_NetSockOperator;
	SocketOperator * o_TerminalSocketOperator;
	MessageProcessor * o_MessageProcessor;
};

#endif /* EVENTLISTENER_H_ */
