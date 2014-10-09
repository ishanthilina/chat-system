/*
 * Server.cpp
 *
 *  Created on: Oct 8, 2014
 *      Author: ishan
 */

#include "Server.h"



void Server::RunServer() {

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
		 

		 //try to specify maximum of 3 pending connections for the master socket
		 if (listen(i_MasterSocket, 3) < 0)
		 {
			 perror("listen");
			 exit(EXIT_FAILURE);
		 }

		 //accept the incoming connection
		 i_Addrlen = sizeof(o_Address);
		 
		 LogDebug("Server.cpp: Listening on port %d", PORT);

		 SocketOperator * pSocketOperator = new SocketOperator();

		 p_DeliveryController= new  DeliveryController(p_ClientRegistry,pSocketOperator);
		 p_MsgBuffer = new MessageBuffer(p_DeliveryController);

		 while(true)
		 {
			 //clear the socket set
			 FD_ZERO(&o_ReadFds);

			 //add master socket to set
			 FD_SET(i_MasterSocket, &o_ReadFds);

			 i_MaxSocketDescriptor= i_MasterSocket;

			 //add child sockets to set
			 for(vector<int>::iterator it=p_ClientDescriptors->begin();it!=p_ClientDescriptors->end();++it)
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
				 p_ClientDescriptors->push_back(i_NewSocket);
				 LogDebug("Server.cpp: Added ip %s , port %d to the listening set.",inet_ntoa(o_Address.sin_addr) , ntohs(o_Address.sin_port));

			 }

			 //else its some IO operation on some other socket
			 for(vector<int>::iterator it=p_ClientDescriptors->begin();it!=p_ClientDescriptors->end();++it)
			 {
				 i_SocketDescriptor = (*it);

				 if (FD_ISSET( i_SocketDescriptor , &o_ReadFds))
				 {
					 //Check if it was for closing , and also read the incoming message
					 if ((i_ReadValue = read( i_SocketDescriptor , z_InputBuffer, MAX_INPUT_BUFFER_SIZE-1)) == 0)
					 {
						 //Somebody disconnected , get his details and print
						 getpeername(i_SocketDescriptor, (struct sockaddr*)&o_Address , (socklen_t*)&i_Addrlen);
						 LogDebug("%s","---------------------------------------------------------------------");
						 LogDebug("Server.cpp: Host disconnected, ip %s , port %d",inet_ntoa(o_Address.sin_addr) , ntohs(o_Address.sin_port));

						 //remove the client info
						 p_ClientRegistry->RemoveClient(p_ClientRegistry->GetClient(i_SocketDescriptor));
						 //Close the socket
						 close( i_SocketDescriptor );
						 //remove the connection from listening sockets
						 p_ClientDescriptors->erase(it);
						 //remove from the clients list also
//						 for(vector<Client*>::iterator it1=o_Clients->begin();it1!=o_Clients->end();++it1)
//						 	{
//							 if ((*it1)->GetSocket()==i_SocketDescriptor)
//							 		{
//							 			delete *it1;
//							 			o_Clients->erase(it1);
//							 			break;
//							 		}
//						 	}


						 break;

					 }
					 else	//if it is not a disconnect
					 {
						 //set the string terminating NULL byte on the end of the data read
						 z_InputBuffer[i_ReadValue] = '\0';

						 LogDebug("%s","---------------------------------------------------------------------");
						 LogDebug("Server.cpp: Incoming message from ip %s , port %d. Message : %s",inet_ntoa(o_Address.sin_addr) , ntohs(o_Address.sin_port),z_InputBuffer);
						 p_MsgBuffer->CreateMessage(i_SocketDescriptor,string(z_InputBuffer),o_Address);

						 break;
					 }

				 }



			 }



		 }
}

Server::Server(ClientRegistry* pclientRegistry)
{
	this->p_ClientRegistry = pclientRegistry;
	p_ClientDescriptors = new vector<int>;

}

Server::~Server() {
	delete p_DeliveryController;
	delete p_MsgBuffer;
}

int main()
{
	ClientRegistry * pClientRegistry= new ClientRegistry();

	Server * pServer = new Server(pClientRegistry);
	pServer->RunServer();


	delete pClientRegistry;

	return 0;
}

