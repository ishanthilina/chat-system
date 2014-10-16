#ifndef _CLIENT_REGISTRY_HEADER_
#define _CLIENT_REGISTRY_HEADER_

#include <vector>

#include "User.h"

using namespace std;


class UserRegistry
{
public:
	UserRegistry();
	int AddUser(User * o_User);
	int RemoveUser(User * o_User);
	bool IsUserExists(string username);
	User * GetUser(Client* pClient);
	User * GetUser(string username);
protected:
private:
	vector<User*> * o_Users;
};

#endif	//_CLIENT_REGISTRY_HEADER_

