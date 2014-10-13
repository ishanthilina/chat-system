/*
 * SocketOperator.cpp
 *
 *  Created on: Oct 5, 2014
 *      Author: ishan
 */

#include "SocketOperator.h"

SocketOperator::SocketOperator()
{
	//this->i_Socket=iSocket;

}

int SocketOperator::ReadFromSocket(int iSocket,char * buffer,int iBufferSize)
{
	int iValRead=0;
	if ((iValRead = read( iSocket , buffer, iBufferSize)) == 0)
	{
		printf("Server Disconnected");
		return 1;
	}
	return 0;
}

int SocketOperator::WriteToSocket(int iSocket,string sBuffer,int iBufferSize)
{
	LogDebug("SocketOperator.cpp - Sending Message - %s",sBuffer.c_str());
	const char * zBuffer=sBuffer.c_str();
	//cout<<zBuffer<<endl;
	int iValWritten=0;
	if ((iValWritten = write( iSocket , zBuffer, iBufferSize)) == 0)
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

