#ifndef _SERVERS_CLIENT_ITERATOR_HEADER_
#define _SERVERS_CLIENT_ITERATOR_HEADER_

class Server;
class Client;

#include "Server.h"
#include "Client.h"

#include <list>

using namespace std;


class ServersClientIterator
{
public:
	Client* First();
	void Next();
	bool IsDone();
	Client* CurrentItem();
	void EraseItem();

	ServersClientIterator(const Server* pServer);
protected:
private:
	list<Client*>* p_Clients;
	std:: list<Client*>::iterator oServerClientIter;
};


#endif	//_SERVERS_CLIENT_ITERATOR_HEADER_
