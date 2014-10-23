/*
 * EventListener.h
 *
 *  Created on: Oct 5, 2014
 *      Author: ishan
 */

#ifndef _EVENT_LISTENER_HEADER_
#define _EVENT_LISTENER_HEADER_

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
#include "MessageFactory.h"
#include "Utils.h"

#define MAX_INPUT_BUFFER_SIZE 1025

class EventListener {
public:
	EventListener(int iSockFD, SocketOperator * pNetSockOperator, SocketOperator * pTerminalSocketOperator,MessageProcessor * pMsgProcessor,MessageFactory * pMessageFactory);
	int Listen();
	virtual ~EventListener();
private:
	int i_SockFD;
	SocketOperator * p_NetSockOperator;
	SocketOperator * p_TerminalSocketOperator;
	MessageProcessor * p_MessageProcessor;
	MessageFactory * p_MessageFactory;
};

#endif /* _EVENT_LISTENER_HEADER_ */
