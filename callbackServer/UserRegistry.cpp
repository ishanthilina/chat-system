#include "UserRegistry.h"

UserRegistry::UserRegistry()
{
	o_Users = new vector<User*>;
}


int UserRegistry::AddUser( User * o_User )
{
	//check if the username is unique
	for(vector<User*>::iterator it=o_Users->begin();it!=o_Users->end();++it)
	{

		if (o_User->GetUserName().compare((*it)->GetUserName())==0)
		{
			return 1;
		}

	}

	o_Users->push_back(o_User);

	return 0;
}


int UserRegistry::RemoveUser( User * o_User )
{

	//remove from the clients list also
	for(vector<User*>::iterator it1=o_Users->begin();it1!=o_Users->end();++it1)
	{
		if ((*it1)==o_User)
		{
			delete *it1;
			o_Users->erase(it1);
			break;
		}
	}

	return 0;
}


bool UserRegistry::IsUserExists( string username )
{
	//check if the username is unique
	for(vector<User*>::iterator it=o_Users->begin();it!=o_Users->end();++it)
	{

		if (username.compare((*it)->GetUserName())==0)
		{
			return true;
		}

	}

	return false;
}




User * UserRegistry::GetUser( string username )
{
	for(vector<User*>::iterator it=o_Users->begin();it!=o_Users->end();++it)
	{


		if (username.compare((*it)->GetUserName())==0)
		{


			return (*it);

		}

	}

	return NULL;

}

User* UserRegistry::GetUser(Client* pClient)
{
	for(vector<User*>::iterator it=o_Users->begin();it!=o_Users->end();++it)
		{

			if (pClient == (*it)->GetClient())
			{
		
				return (*it);

			}

		}

		return NULL;
}
