/*
 * Server.h
 *
 *  Created on: Oct 13, 2014
 *      Author: ishan
 */

#ifndef SERVER_H_
#define SERVER_H_

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
	vector<Client*> GetClients();

private:
	int i_SocketFd;
	vector<Client*> p_Clients;


};

#endif /* SERVER_H_ */
