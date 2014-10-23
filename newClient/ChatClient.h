/*
 * ChatClient.h
 *
 *  Created on: Oct 5, 2014
 *      Author: ishan
 */

#ifndef _CHAT_CLIENT_HEADER_
#define _CHAT_CLIENT_HEADER_

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

#include "SocketOperator.h"
#include "MessageProcessor.h"
#include "MessageParser.h"
#include "EventListener.h"
#include "MessageFactory.h"
#include "Utils.h"
#include "ScreenWriter.h"

#define SLEEP_TIME 1000000

class ChatClient {
public:
	ChatClient();
	int StartClient();
	virtual ~ChatClient();
private:
	int Connect();
};

#endif /* _CHAT_CLIENT_HEADER_ */
