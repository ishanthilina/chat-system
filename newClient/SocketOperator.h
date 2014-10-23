/*
 * SocketOperator.h
 *
 *  Created on: Oct 5, 2014
 *      Author: ishan
 */

#ifndef _SOCKET_OPERATOR_HEADER_
#define _SOCKET_OPERATOR_HEADER_

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <netdb.h>
#include <iostream>

#include "Utils.h"



class SocketOperator {
public:
	SocketOperator(int iSocket);
	int ReadFromSocket(char * zBuffer,int iBufferSize);
	int WriteToSocket(const char * zBuffer,int iBufferSize);

	virtual ~SocketOperator();
private:
	int i_Socket;
};

#endif /* _SOCKET_OPERATOR_HEADER_ */
