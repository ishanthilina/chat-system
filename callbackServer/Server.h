/*
 * Server.h
 *
 *  Created on: Oct 13, 2014
 *      Author: ishan
 */

#ifndef _SERVER_HEADER_
#define _SERVER_HEADER_

#include <string>
#include <vector>

#include "Utils.h"
#include "Client.h"

using namespace std;

class Server {
public:
	Server(int iSocketFd);
	virtual ~Server();

	int GetSocket();
	void AddClient(Client* pClient);
	vector<Client*>* GetClients();//TODO: provide an iterator pattern

private:
	int i_SocketFd;
	vector<Client*>* p_Clients; //TODO should  ideally be a list


};

#endif /* _SERVER_HEADER_ */
