/*
 * Server.h
 *
 *  Created on: Oct 13, 2014
 *      Author: ishan
 */

#ifndef _SERVER_HEADER_
#define _SERVER_HEADER_

#include <string>
#include <list>
#include <errno.h>

class SCallBack;
class Client;
class ServersClientIterator;

#include "Utils.h"
#include "Client.h"
#include "ServersClientIterator.h"
#include "SCallBack.h"

using namespace std;



class Server {
public:
	Server(int iSocketFd, SCallBack* pSCallBack);
	virtual ~Server();

	int GetSocket();
	void AddClient(Client* pClient);
	void ProcessServerEvent();
	ServersClientIterator* GetClientIterator();
	void DeleteClient(Client* pClient);

	friend class ServersClientIterator;
	

private:
	int i_SocketFd;
	list<Client*>* p_Clients;
	SCallBack* p_SCallBack;



};

#endif /* _SERVER_HEADER_ */
