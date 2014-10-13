/*
 * SocketOperator.h
 *
 *  Created on: Oct 5, 2014
 *      Author: ishan
 */

#ifndef SOCKETOPERATOR_H_
#define SOCKETOPERATOR_H_

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

using namespace std;

class SocketOperator {
public:
	SocketOperator();
	int ReadFromSocket(int iSocket,char * buffer,int iBufferSize);
	int WriteToSocket(int iSocket,string sBuffer,int iBufferSize);

	virtual ~SocketOperator();
private:
	//int i_Socket;
};

#endif /* SOCKETOPERATOR_H_ */
