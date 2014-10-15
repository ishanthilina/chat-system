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
	// TODO Auto-generated destructor stub
}

int Client::GetSocket()
{
	return this->i_SocketFd;
}

void Client::SendMessage( string sMessage )
{
	LogDebug("Client.cpp: Sending %s",sMessage.c_str());

	int iValWritten=0;
	if ((iValWritten = write( i_SocketFd , sMessage.c_str(), sMessage.length())) == 0)
	{
		LogDebug("Client.cpp: %s","Error writing to socket");
		//return 1;
		return;
	}
	//return 0;
}



