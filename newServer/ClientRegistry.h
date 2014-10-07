#ifndef _CLIENT_REGISTRY_HEADER_
#define _CLIENT_REGISTRY_HEADER_

#include "Client.h"


class ClientRegistry
{
public:
	ClientRegistry();
	int AddClient(Client * o_Client);
	int RemoveClient(Client * o_Client);
	bool IsClientExists(string username);
	Client * GetClient(int i_socket);
	Client * GetClient(string username);
protected:
private:
	vector<Client*> * o_Clients;
};

#endif	//_CLIENT_REGISTRY_HEADER_

