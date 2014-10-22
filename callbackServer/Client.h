/*
 * Client.h
 *
 *  Created on: Oct 13, 2014
 *      Author: ishan
 */

#ifndef _CLIENT_HEADER_
#define _CLIENT_HEADER_

#include <string>
 #include <sys/socket.h>
#include <netdb.h>
#include <sys/types.h>
#include <unistd.h>   //defines read

#include "Utils.h"

using namespace std;

class Client {
public:
	Client(int iSocketFd);
	virtual ~Client();

	int SendMessage(string sMessage);
	int GetSocket();
private:
	int i_SocketFd;
};

#endif /* _CLIENT_HEADER_ */
