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

int SocketOperator::ReadFromSocket(char * zBuffer,int iBufferSize)
{
	int iValRead=0;
	if ((iValRead = read( i_Socket , zBuffer, iBufferSize)) == 0)
	{
		LogDebug("SocketOperator.cpp - Server %s","Disconnected");
		return 0;
	}
	return iValRead;
}

int SocketOperator::WriteToSocket(const char * zBuffer,int iBufferSize)
{
	LogDebug("SocketOperator.cpp - Sending Message - %s",zBuffer);
	int iValWritten=0;
	if ((iValWritten = write( i_Socket , zBuffer, iBufferSize)) == 0)
	{

		LogDebug("SocketOperator.cpp - Error writing to  %s","socket");
		return 1;
	}
	return 0;
}


SocketOperator::~SocketOperator()
{

}

