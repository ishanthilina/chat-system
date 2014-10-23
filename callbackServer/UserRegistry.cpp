#include "UserRegistry.h"

UserRegistry::UserRegistry()
{
	p_Users = new vector<User*>;
}


int UserRegistry::AddUser( User * pUser )
{
	//check if the username is unique
	for(vector<User*>::iterator it=p_Users->begin();it!=p_Users->end();++it)
	{

		if (pUser->GetUserName().compare((*it)->GetUserName())==0)
		{
			return 1;
		}

	}

	p_Users->push_back(pUser);

	return 0;
}


int UserRegistry::RemoveUser( User * pUser )
{

	//remove from the clients list also
	for(vector<User*>::iterator it1=p_Users->begin();it1!=p_Users->end();++it1)
	{
		if ((*it1)==pUser)
		{
			delete *it1;
			p_Users->erase(it1);
			break;
		}
	}

	return 0;
}


bool UserRegistry::IsUserExists( string sUsername )
{
	//check if the username is unique
	for(vector<User*>::iterator it=p_Users->begin();it!=p_Users->end();++it)
	{

		if (sUsername.compare((*it)->GetUserName())==0)
		{
			return true;
		}

	}

	return false;
}




User * UserRegistry::GetUser( string sUsername )
{
	for(vector<User*>::iterator it=p_Users->begin();it!=p_Users->end();++it)
	{


		if (sUsername.compare((*it)->GetUserName())==0)
		{


			return (*it);

		}

	}

	return NULL;

}

User* UserRegistry::GetUser(Client* pClient)
{
	for(vector<User*>::iterator it=p_Users->begin();it!=p_Users->end();++it)
		{

			if (pClient == (*it)->GetClient())
			{
		
				return (*it);

			}

		}

		return NULL;
}
