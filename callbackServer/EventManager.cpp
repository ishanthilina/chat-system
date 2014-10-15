/*
 * EventManager.cpp
 *
 *  Created on: Oct 13, 2014
 *      Author: ishan
 */

#include "EventManager.h"

EventManager::EventManager() {
	// TODO Auto-generated constructor stub

}

EventManager::~EventManager() {
	// TODO Auto-generated destructor stub
}

Server* EventManager::CreateServer(int iPort, SCallBack* pCallBack)
{
	int iMasterSocket,      iOption=1;
	struct sockaddr_in o_Address;

	//create a master socket
	if( (iMasterSocket = socket(AF_INET , SOCK_STREAM , 0)) == 0)
	{
		perror("socket failed");
		exit(EXIT_FAILURE);
	}

	//set master socket to allow multiple connections , this is just a good habit, it will work without this
	if( setsockopt(iMasterSocket, SOL_SOCKET, SO_REUSEADDR, (char *)&iOption, sizeof(iOption)) < 0 )
	{
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}

	//type of socket created
	o_Address.sin_family = AF_INET;
	o_Address.sin_addr.s_addr = INADDR_ANY;
	o_Address.sin_port = htons( iPort );

	//bind the socket to localhost port 8888
	if (bind(iMasterSocket, (struct sockaddr *)&o_Address, sizeof(o_Address))<0)
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}


	//try to specify maximum of 3 pending connections for the master socket
	if (listen(iMasterSocket, 3) < 0)
	{
		perror("listen");
		exit(EXIT_FAILURE);
	}

	Server* pServer=new Server(iMasterSocket);
	this->p_CallBackHandler=pCallBack;
	this->mServers.insert ( std::pair<int,Server*>(iMasterSocket,pServer) );

	return pServer;

}

Client* EventManager::CreateClient(char* zHost, int iPort,
		SCallBack* pCallBack)
{
	int sockfd;
	struct sockaddr_in serv_addr;
	struct hostent *server;


	/* Create a socket point */
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
	{
		perror("ERROR opening socket");
		//return 1;
	}
	server = gethostbyname(zHost);
	if (server == NULL) {
		fprintf(stderr,"ERROR, no such host\n");
		//return 0;
	}

	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy((char *)server->h_addr,
			(char *)&serv_addr.sin_addr.s_addr,
			server->h_length);
	serv_addr.sin_port = htons(iPort);

	/* Now connect to the server */
	if (connect(sockfd,(sockaddr*)&serv_addr,sizeof(serv_addr)) < 0)
	{
		perror("ERROR connecting");
		//return 1;
	}

	Client * pClient=new Client(sockfd);
	this->mClients.insert ( std::pair<int,Client*>(sockfd,pClient) );
	return pClient;
}




int EventManager::Run()
{
	char z_InputBuffer[MAX_INPUT_BUFFER_SIZE];  //input data buffer
	int i_MaxSocketDescriptor, i_SocketDescriptor,i_SocketActivity,i_NewSocket,i_Addrlen,i_ReadValue;
	struct sockaddr_in o_Address;

	 while(true)
		 {
			 //clear the socket set
			 FD_ZERO(&o_ReadFds);

			 //add STDIN to set
			 FD_SET(STDIN_FILENO, &o_ReadFds);

			 LogDebug("EventManager.cpp: Refreshing listening socket %s","descriptors");

			 i_MaxSocketDescriptor= 0;
			 //itetrate all the clients
			 std::map<int, Client*>::iterator oClientIter;
			 for (oClientIter = mClients.begin(); oClientIter != mClients.end(); ++oClientIter) 
			 {
				 i_SocketDescriptor = oClientIter->second->GetSocket();
				 FD_SET( i_SocketDescriptor , &o_ReadFds);
				 //highest file descriptor number, need it for the select function
				 if(i_SocketDescriptor > i_MaxSocketDescriptor)
					 i_MaxSocketDescriptor = i_SocketDescriptor;

			 }

				//iterate the servers 
			 std::map<int, Server*>::iterator  oServerIter;
			 for (oServerIter = mServers.begin(); oServerIter != mServers.end(); ++oServerIter) 
			 {
				 i_SocketDescriptor = oServerIter->second->GetSocket();
				 FD_SET( i_SocketDescriptor , &o_ReadFds);
				 //highest file descriptor number, need it for the select function
				 if(i_SocketDescriptor > i_MaxSocketDescriptor)
					 i_MaxSocketDescriptor = i_SocketDescriptor;

				 vector<Client*> pClients=oServerIter->second->GetClients();
				 std:: vector<Client*>::iterator oServerClientIter;
				 for (oServerClientIter = pClients.begin(); oServerClientIter != pClients.end(); ++oServerClientIter) 
				 {
					 i_SocketDescriptor = (*oServerClientIter)->GetSocket();
					 FD_SET( i_SocketDescriptor , &o_ReadFds);
					 //highest file descriptor number, need it for the select function
					 if(i_SocketDescriptor > i_MaxSocketDescriptor)
						 i_MaxSocketDescriptor = i_SocketDescriptor;
				 }

			 }
			 LogDebug("EventManager.cpp: Refreshing listening socket %s","descriptors - done");
			

			 //wait for an activity on one of the sockets , timeout is NULL , so wait indefinitely
			 i_SocketActivity = select( i_MaxSocketDescriptor + 1 , &o_ReadFds , NULL , NULL , NULL);

			 if ((i_SocketActivity < 0) && (errno!=EINTR))
			 {
				 printf("select error");
			 }

			 LogDebug("EventManager.cpp: Receiving %s","Message");

			 //check the STDIN
			 if (FD_ISSET(STDIN_FILENO, &o_ReadFds))
			 {
				 if ((i_ReadValue = read( STDIN_FILENO , z_InputBuffer, MAX_INPUT_BUFFER_SIZE-1)) == 0)
				 {
					 perror("accept");
					 exit(EXIT_FAILURE);
				 }
				 else{
					 z_InputBuffer[i_ReadValue] = '\0';
					LogDebug("Terminal input: %s",z_InputBuffer);
					
					for (oClientIter = mClients.begin(); oClientIter != mClients.end(); ++oClientIter) 
					{

						oClientIter->second->SendMessage(string(z_InputBuffer));

					}
				 }
				 
			 }
			 

			 //check the servers
			 
			 for (oServerIter = mServers.begin(); oServerIter != mServers.end(); ++oServerIter) 
			 {

				 i_SocketDescriptor = oServerIter->second->GetSocket();
				 //If something happened on a server socket , then its an incoming connection
				 if (FD_ISSET(i_SocketDescriptor, &o_ReadFds))
				 {
					 LogDebug("EventManager.cpp: Receiving Message from %s","Server");
					 if ((i_NewSocket = accept(i_SocketDescriptor, (struct sockaddr *)&o_Address, (socklen_t*)&i_Addrlen))<0)
					 {
						 perror("accept");
						 exit(EXIT_FAILURE);
					 }

					 //Create client and notify
					 Client* pClient=new Client(i_NewSocket);
					oServerIter->second->AddClient(pClient);
					 this->p_CallBackHandler->OnConnect(&(*oServerIter->second),pClient);
					

				 }

				 //check for IO operations from the clients of this server
				 vector<Client*> pClients=oServerIter->second->GetClients();
				 std:: vector<Client*>::iterator oServerClientIter;
				 for (oServerClientIter = pClients.begin(); oServerClientIter != pClients.end(); ++oServerClientIter) 
				 {
					 i_SocketDescriptor = (*oServerClientIter)->GetSocket();
					 if (FD_ISSET(i_SocketDescriptor, &o_ReadFds))
					 {
						 LogDebug("EventManager.cpp: Receiving Message from %s","Client");
						 //Check if it was for closing , and also read the incoming message
						 if ((i_ReadValue = read( i_SocketDescriptor , z_InputBuffer, MAX_INPUT_BUFFER_SIZE-1)) == 0)
						 {
							 //Somebody disconnected , get his details and print
							 getpeername(i_SocketDescriptor, (struct sockaddr*)&o_Address , (socklen_t*)&i_Addrlen);
							 LogDebug("%s","---------------------------------------------------------------------");
							 LogDebug("EventManager: Host disconnected, ip %s , port %d",inet_ntoa(o_Address.sin_addr) , ntohs(o_Address.sin_port));

							 this->p_CallBackHandler->OnDisconnect(&(*oServerIter->second),(*oServerClientIter));

							 //remove from the servers clients as well
							 pClients.erase(oServerClientIter);


						}
						 else{
							 z_InputBuffer[i_ReadValue] = '\0';

							 LogDebug("%s","---------------------------------------------------------------------");
							 LogDebug("EventManager: Incoming message from ip %s , port %d. Message : %s",inet_ntoa(o_Address.sin_addr) , ntohs(o_Address.sin_port),z_InputBuffer);
							 this->p_CallBackHandler->OnData(&(*oServerIter->second),(*oServerClientIter),string(z_InputBuffer));
						 }

					 }

				}

			}

			

			 //check for activity in the clients as well
			 
			 for (oClientIter = mClients.begin(); oClientIter != mClients.end(); ++oClientIter) 
			 {
				 i_SocketDescriptor = oClientIter->second->GetSocket();
				 if (FD_ISSET(i_SocketDescriptor, &o_ReadFds))
				 {
					LogDebug("EventManager.cpp: Receiving Message from %s","Server");

					//Check if it was for closing , and also read the incoming message
					if ((i_ReadValue = read( i_SocketDescriptor , z_InputBuffer, MAX_INPUT_BUFFER_SIZE-1)) == 0)
					{
						
						LogDebug("%s","---------------------------------------------------------------------");
						LogDebug("EventManager: Server disconnected, ip %s , port %d",inet_ntoa(o_Address.sin_addr) , ntohs(o_Address.sin_port));

						this->p_CallBackHandler->OnDisconnect((*oClientIter).second);

						//remove from the servers clients as well
						mClients.erase(oClientIter);


					}
					else{
						z_InputBuffer[i_ReadValue] = '\0';

						LogDebug("%s","---------------------------------------------------------------------");
						LogDebug("EventManager: Incoming message from Server ip %s , port %d. Message : %s",inet_ntoa(o_Address.sin_addr) , ntohs(o_Address.sin_port),z_InputBuffer);
						this->p_CallBackHandler->OnData((*oClientIter).second,"Server Data");
					}

				 }

			 }


			 

			 



		 }
}
