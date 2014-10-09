/*
 * Server.h
 *
 *  Created on: Oct 8, 2014
 *      Author: ishan
 */

#ifndef SERVER_H_
#define SERVER_H_

#include <string>
#include <string.h>   //strlen
#include <iostream>
#include <stdio.h>	//defines perror
#include <stdlib.h>	//defines  exit and EXIT_FAILURE
#include <sys/time.h> //FD_SET, FD_ISSET, FD_ZERO macros
#include <errno.h>

#include <arpa/inet.h>    //close, AF_INET
#include <unistd.h>   //defines read

#include <vector>

#include "MessageBuffer.h"
#include "ClientRegistry.h"
#include "Utils.h"

using namespace std;

#define MAX_INPUT_BUFFER_SIZE 1025
#define PORT 8888

class Server {
public:
	Server(ClientRegistry * pclientRegistry);
	void RunServer();
	virtual ~Server();
private:
	vector<int> * p_ClientDescriptors;
	MessageBuffer * p_MsgBuffer;
	DeliveryController * p_DeliveryController;
	ClientRegistry * p_ClientRegistry;
};

#endif /* SERVER_H_ */
