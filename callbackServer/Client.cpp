/*
 * Client.cpp
 *
 *  Created on: Oct 13, 2014
 *      Author: ishan
 */

#include "Client.h"

Client::Client(int iSocketFd) {
	this->i_SocketFd=iSocketFd;

}

Client::~Client() {

}

int Client::GetSocket()
{
	return this->i_SocketFd;
}

int Client::SendMessage(string sMessage)
{
	LogDebug("Client.cpp: Sending to socket %d : %s",i_SocketFd,sMessage.c_str());

	int iValWritten=0;
	if ((iValWritten = write( i_SocketFd , sMessage.c_str(), sMessage.length())) == 0)//TODO: handle the buffering of the server socket.
	{
		LogDebug("Client.cpp: %s","Error writing to socket");

	}
	return iValWritten;
}



