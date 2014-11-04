#ifndef _CLIENT_REGISTRY_HEADER_
#define _CLIENT_REGISTRY_HEADER_

#include <list>

#include "User.h"

using namespace std;


class UserRegistry
{
public:
	UserRegistry();
	int AddUser(User * pUser);
	int RemoveUser(User * pUser);
	bool IsUserExists(string sUsername);
	User * GetUser(Client* pClient);
	User * GetUser(string sUsername);
protected:
private:
	list<User*> * lst_Users;
};

#endif	//_CLIENT_REGISTRY_HEADER_

