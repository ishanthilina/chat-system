/*
 * Server.cpp
 *
 *  Created on: Oct 13, 2014
 *      Author: ishan
 */

#include "Server.h"

Server::Server(int iSocketFd) {
	i_SocketFd=iSocketFd;
	p_Clients=new vector<Client*>();

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

vector<Client*>* Server::GetClients()
{
	return p_Clients;
}




