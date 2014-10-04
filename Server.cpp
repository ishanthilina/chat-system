#include "Server.h"


#define MAX_INPUT_BUFFER_SIZE 1025
#define PORT 8888

Server::Server( MessageFactory * p_MsgFactory,DeliveryController * p_MsgProcessor )
{
	this->p_MsgFactory=p_MsgFactory;
	this->p_MsgProcessor=p_MsgProcessor;
	o_Clients = new vector<Client*>;
	o_ClientDescriptors = new vector<int>;
}

void Server::RunServer()
{
	

	int i_MasterSocket, i_Addrlen, i_NewSocket, i_SocketActivity, i_ReadValue, i_SocketDescriptor, i_MaxSocketDescriptor, i_Option=1;
	struct sockaddr_in o_Address;

	char z_InputBuffer[MAX_INPUT_BUFFER_SIZE];  //input data buffer

	 //set of socket descriptors
	 fd_set o_ReadFds;

	 //create a master socket
	 if( (i_MasterSocket = socket(AF_INET , SOCK_STREAM , 0)) == 0)
	 {
	     perror("socket failed");
	     exit(EXIT_FAILURE);
	 }

	 //set master socket to allow multiple connections , this is just a good habit, it will work without this
	 if( setsockopt(i_MasterSocket, SOL_SOCKET, SO_REUSEADDR, (char *)&i_Option, sizeof(i_Option)) < 0 )
	 {
		 perror("setsockopt");
		 exit(EXIT_FAILURE);
	 }

	 //type of socket created
	 o_Address.sin_family = AF_INET;
	 o_Address.sin_addr.s_addr = INADDR_ANY;
	 o_Address.sin_port = htons( PORT );

	 //bind the socket to localhost port 8888
	 if (bind(i_MasterSocket, (struct sockaddr *)&o_Address, sizeof(o_Address))<0)
	 {
		 perror("bind failed");
		 exit(EXIT_FAILURE);
	 }
	 //LogDebug("Listener on port %d \n", PORT);

	 //try to specify maximum of 3 pending connections for the master socket
	 if (listen(i_MasterSocket, 3) < 0)
	 {
		 perror("listen");
		 exit(EXIT_FAILURE);
	 }

	 //accept the incoming connection
	 i_Addrlen = sizeof(o_Address);
	 puts("Waiting for connections ...");

	 while(true)
	 {
		 //clear the socket set
		 FD_ZERO(&o_ReadFds);

		 //add master socket to set
		 FD_SET(i_MasterSocket, &o_ReadFds);

		 i_MaxSocketDescriptor= i_MasterSocket;

		 //add child sockets to set
		 for(vector<int>::iterator it=o_ClientDescriptors->begin();it!=o_ClientDescriptors->end();++it)
		 {
			 i_SocketDescriptor = (*it);
			 FD_SET( i_SocketDescriptor , &o_ReadFds);

			 //highest file descriptor number, need it for the select function
			 if(i_SocketDescriptor > i_MaxSocketDescriptor)
				 i_MaxSocketDescriptor = i_SocketDescriptor;


		 }

		 //wait for an activity on one of the sockets , timeout is NULL , so wait indefinitely
		 i_SocketActivity = select( i_MaxSocketDescriptor + 1 , &o_ReadFds , NULL , NULL , NULL);

		 if ((i_SocketActivity < 0) && (errno!=EINTR))
		 {
			 printf("select error");
		 }

		 //If something happened on the master socket , then its an incoming connection
		 if (FD_ISSET(i_MasterSocket, &o_ReadFds))
		 {
			 if ((i_NewSocket = accept(i_MasterSocket, (struct sockaddr *)&o_Address, (socklen_t*)&i_Addrlen))<0)
			 {
				 perror("accept");
				 exit(EXIT_FAILURE);
			 }

			 //add new socket to the watching set of sockets
			 o_ClientDescriptors->push_back(i_NewSocket);

		 }

		 //else its some IO operation on some other socket
		 for(vector<int>::iterator it=o_ClientDescriptors->begin();it!=o_ClientDescriptors->end();++it)
		 {
			 i_SocketDescriptor = (*it);

			 if (FD_ISSET( i_SocketDescriptor , &o_ReadFds))
			 {
				 //Check if it was for closing , and also read the incoming message
				 if ((i_ReadValue = read( i_SocketDescriptor , z_InputBuffer, MAX_INPUT_BUFFER_SIZE-1)) == 0)
				 {
					 //Somebody disconnected , get his details and print
					 getpeername(i_SocketDescriptor, (struct sockaddr*)&o_Address , (socklen_t*)&i_Addrlen);
					 printf("Host disconnected , ip %s , port %d \n" , inet_ntoa(o_Address.sin_addr) , ntohs(o_Address.sin_port));

					 //Close the socket and mark as 0 in list for reuse


					 //TODO - Handle close logic
					 close( i_SocketDescriptor );
					 //remove the connection from listening sockets
					 o_ClientDescriptors->erase(it);
					 //remove from the clients list also
					 for(vector<Client*>::iterator it1=o_Clients->begin();it1!=o_Clients->end();++it1)
					 	{
						 if ((*it1)->GetSocket()==i_SocketDescriptor)
						 		{
						 			delete *it1;
						 			o_Clients->erase(it1);
						 			break;
						 		}
					 	}
					 break;

				 }
				 else	//if it is not a disconnect
				 {
					 //set the string terminating NULL byte on the end of the data read
					 z_InputBuffer[i_ReadValue] = '\0';

					 Message * oMmessage=p_MsgFactory->createMessage(i_SocketDescriptor,string(z_InputBuffer),o_Address);
					 p_MsgProcessor->processMessage(oMmessage);
					 //cout<<"Server:: "<<oMmessage->GetMessage()<<endl;
					 delete oMmessage;
				 }

			 }



		 }



	 }

	//////////////////////////////////////////////////

//	string testMsg = "LIN;ishanthilina";
//	//string testMsg = "P2P;ishanthilina,thisarar;my Message";
//	//string testMsg = "DDD;ishanthilina,thisarar;my Message";
//	//
//	sockaddr_in ss;
//
//	Message * oMmessage=p_MsgFactory->createMessage(1,testMsg,ss);
//	p_MsgProcessor->processMessage(oMmessage);
//
//
//	cout<<"Server:: "<<oMmessage->GetMessage()<<endl;
//
//	delete oMmessage;
}

int Server::AddClient( Client * o_Client )
{
	printf("SERVER:: Add Client - %s\n",o_Client->GetLogName().c_str());

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

int Server::SendMessage( string s_Message, int i_socket )
{


	if( send(i_socket, s_Message.c_str(), strlen(s_Message.c_str()), 0) != strlen(s_Message.c_str()) ) 
	{
		perror("send");
		return 1;
	}

	return 0;

}

bool Server::IsClientExists( string username )
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

Client * Server::GetClient( int i_socket )
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

Client * Server::GetClient( string username )
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

int main(){

	MessageFactory * pFactory = new MessageFactory();
	Logger * pLogger = new Logger();
	DeliveryController * pController = new DeliveryController(pLogger);
	Server * pServer=new Server(pFactory,pController);
	pController->setServer(pServer);
	pServer->RunServer();

	delete pFactory;
	delete pLogger;
	delete pController;
	delete pServer;
	//cout<<"main"<<endl;
}
