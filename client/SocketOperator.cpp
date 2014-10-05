/*
 * SocketOperator.cpp
 *
 *  Created on: Oct 5, 2014
 *      Author: ishan
 */

#include "SocketOperator.h"

SocketOperator::SocketOperator(int iSocket)
{
	this->i_Socket=iSocket;

}

int SocketOperator::ReadFromSocket(char * buffer,int iBufferSize)
{
	int iValRead=0;
	if ((iValRead = read( i_Socket , buffer, iBufferSize)) == 0)
	{
		printf("Server Disconnected");
		return 1;
	}
	return 0;
}

int SocketOperator::WriteToSocket(char * buffer,int iBufferSize)
{
	int iValWritten=0;
	if ((iValWritten = write( i_Socket , buffer, iBufferSize)) == 0)
	{
		printf("Error writing to socket");
		return 1;
	}
	return 0;
}


SocketOperator::~SocketOperator()
{
	// TODO Auto-generated destructor stub
}

