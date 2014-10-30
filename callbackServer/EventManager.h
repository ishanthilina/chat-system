/*
 * EventManager.h
 *
 *  Created on: Oct 13, 2014
 *      Author: ishan
 */

#ifndef _EVENTMANAGER_HEADER_
#define _EVENTMANAGER_HEADER_

#include <string>
#include <string.h>   //strlen
#include <iostream>
#include <stdio.h>	//defines perror
#include <stdlib.h>	//defines  exit and EXIT_FAILURE
#include <sys/time.h> //FD_SET, FD_ISSET, FD_ZERO macros
#include <errno.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <arpa/inet.h>    //close, AF_INET
#include <unistd.h>   //defines read
#include <errno.h>

#include <map>

#include "Server.h"
#include "Client.h"
#include "SCallBack.h"
#include "Utils.h"


#define MAX_INPUT_BUFFER_SIZE 1025

class EventManager {
public:
	EventManager();
	virtual ~EventManager();

	Server* CreateServer(int iPort, SCallBack * pCallBack);
	Client* CreateClient(char * zHost, int iPort, SCallBack * pCallBack);
	int Run();

private:
	//set of socket descriptors
	fd_set oReadFds;
	SCallBack * p_CallBackHandler;

	map<int, Client* > mClients;//TODO: use correct prefix
	map<int, Server* > mServers;

};

#endif /* _EVENTMANAGER_HEADER_ */
