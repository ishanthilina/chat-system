/*
 * Server.cpp
 *
 *  Created on: Oct 13, 2014
 *      Author: ishan
 */

#include "Server.h"

Server::Server(int iSocketFd) {
	this->i_SocketFd=iSocketFd;
	//this->p_Clients=new vector<Client*>();

}



Server::~Server() {
	// TODO Auto-generated destructor stub
}

int Server::GetSocket()
{
	return this->i_SocketFd;
}

void Server::AddClient( Client* pClient )
{
		this->p_Clients.push_back(pClient);
}

vector<Client*> Server::GetClients()
{
	return p_Clients;
}




