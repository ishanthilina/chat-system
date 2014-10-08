#include "ClientRegistry.h"

ClientRegistry::ClientRegistry()
{
	o_Clients = new vector<Client*>;
}


int ClientRegistry::AddClient( Client * o_Client )
{
	//check if the username is unique
	for(vector<Client*>::iterator it=o_Clients->begin();it!=o_Clients->end();++it)
	{

		if (o_Client->GetUserName().compare((*it)->GetUserName())==0)
		{
			return 1;
		}

	}

	o_Clients->push_back(o_Client);

	return 0;
}


int ClientRegistry::RemoveClient( Client * o_Client )
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
	for(vector<Client*>::iterator it1=o_Clients->begin();it1!=o_Clients->end();++it1)
	{
		if ((*it1)->GetSocket()==o_Client->GetSocket())
		{
			delete *it1;
			o_Clients->erase(it1);
			break;
		}
	}

	return 0;
}


bool ClientRegistry::IsClientExists( string username )
{
	//check if the username is unique
	for(vector<Client*>::iterator it=o_Clients->begin();it!=o_Clients->end();++it)
	{
		//cout<<username<<"-"<<(*it)->GetUserName()<<endl;

		if (username.compare((*it)->GetUserName())==0)
		{
			return true;
		}

	}

	return false;
}


Client * ClientRegistry::GetClient( int i_socket )
{
	for(vector<Client*>::iterator it=o_Clients->begin();it!=o_Clients->end();++it)
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



Client * ClientRegistry::GetClient( string username )
{
	for(vector<Client*>::iterator it=o_Clients->begin();it!=o_Clients->end();++it)
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
