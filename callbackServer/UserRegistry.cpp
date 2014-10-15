#include "ClientRegistry.h"

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
	//Close the socket
//	close( o_Client->GetSocket() );
//	//remove the connection from listening sockets
//	for(vector<int>::iterator it=o_ClientDescriptors->begin();it!=o_ClientDescriptors->end();++it)
//	{
//		if(o_Client->GetSocket() ==(*it)){
//			o_ClientDescriptors->erase(it);
//			break;
//		}
//
//	}

	//remove from the clients list also
	for(vector<User*>::iterator it1=o_Users->begin();it1!=o_Users->end();++it1)
	{
		if ((*it1)->GetSocket()==o_User->GetSocket())
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
		//cout<<username<<"-"<<(*it)->GetUserName()<<endl;

		if (username.compare((*it)->GetUserName())==0)
		{
			return true;
		}

	}

	return false;
}


User * UserRegistry::GetUser( int i_socket )
{
	for(vector<User*>::iterator it=o_Users->begin();it!=o_Users->end();++it)
	{
		//cout<<username<<"-"<<(*it)->GetUserName()<<endl;

		if (i_socket==(*it)->GetSocket())
		{
			//oClient = new Client((*it)->GetUserName(),(*it)->GetSocket(),(*it)->GetAddressStruct());
			//cout<<"-"<<(*it)->GetUserName()<<endl;

			return (*it);

			//return 0;
		}

	}

	return NULL;
}



User * UserRegistry::GetUser( string username )
{
	for(vector<User*>::iterator it=o_Users->begin();it!=o_Users->end();++it)
	{
		//cout<<username<<"-"<<(*it)->GetUserName()<<endl;

		if (username.compare((*it)->GetUserName())==0)
		{
			//oClient = new Client((*it)->GetUserName(),(*it)->GetSocket(),(*it)->GetAddressStruct());
			//cout<<"-"<<(*it)->GetUserName()<<endl;

			return (*it);

			//return 0;
		}

	}

	return NULL;

}
