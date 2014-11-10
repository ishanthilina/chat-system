/*
 * Server.cpp
 *
 *  Created on: Oct 13, 2014
 *      Author: ishan
 */

#include "Server.h"

Server::Server(int iSocketFd, SCallBack* pSCallBack) {
	i_SocketFd=iSocketFd;
	p_SCallBack = pSCallBack;
	p_Clients=new list<Client*>();

}



Server::~Server() {

}

int Server::GetSocket()
{
	return i_SocketFd;
}

void Server::AddClient( Client* pClient )
{
		(*p_Clients).push_back(pClient);
}

ServersClientIterator* Server::GetClientIterator()
{
	return new ServersClientIterator(this);
}

void Server::ProcessServerEvent()
{
	int iNewSocket=-1, iAddrlen=0;
	struct sockaddr_in oAddress;
	LogDebug("Server.cpp: Receiving Message from Server socket: %d",i_SocketFd);
	if ((iNewSocket = accept(i_SocketFd, (struct sockaddr *)&oAddress, (socklen_t*)&iAddrlen))<0)
	{
		printf("Server.cpp: Error in accepting connection in server socket %d. ErrorNo: %d , ErrorMsg: %s", i_SocketFd, errno,strerror(errno));
		return;
	}

	//Create client and notify
	Client* pClient=new Client(iNewSocket, p_SCallBack);
	p_Clients->push_back(pClient);
	p_SCallBack->OnConnect(this,pClient);
}

void Server::DeleteClient( Client* pClient )
{
	std:: list<Client*>::iterator oServerClientIter;
	for (oServerClientIter = (*p_Clients).begin(); oServerClientIter != (*p_Clients).end(); ++oServerClientIter)
	{
		if ( pClient == (*oServerClientIter) )
		{
			LogDebug("Server.cpp:Deleting client of socket: %d",(*oServerClientIter)->GetSocket());
			p_Clients->erase(oServerClientIter);
			break;
		}
		
	}
}







