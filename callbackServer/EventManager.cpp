/*
 * EventManager.cpp
 *
 *  Created on: Oct 13, 2014
 *      Author: ishan
 */

#include "EventManager.h"

EventManager::EventManager() {


}

EventManager::~EventManager() {

}

Server* EventManager::CreateServer(int iPort, SCallBack* pCallBack)
{
	int iMasterSocket,      iOption=1;
	struct sockaddr_in oAddress;

	//create a master socket
	if( (iMasterSocket = socket(AF_INET , SOCK_STREAM , 0)) == 0)
	{
		printf("EventManager.cpp: Error in creating socket. ErrorNo: %d , ErrorMsg: %s\n", errno,strerror(errno));
		exit(EXIT_FAILURE);
	}

	//set master socket to allow multiple connections , this is just a good habit, it will work without this
	if( setsockopt(iMasterSocket, SOL_SOCKET, SO_REUSEADDR, (char *)&iOption, sizeof(iOption)) < 0 )
	{
		printf("EventManager.cpp: Error in setting socket options. ErrorNo: %d , ErrorMsg: %s\n", errno,strerror(errno));
		exit(EXIT_FAILURE);
	}

	//type of socket created
	oAddress.sin_family = AF_INET;
	oAddress.sin_addr.s_addr = INADDR_ANY;
	oAddress.sin_port = htons( iPort );

	//bind the socket to localhost port 8888
	if (bind(iMasterSocket, (struct sockaddr *)&oAddress, sizeof(oAddress))<0)
	{
		printf("EventManager.cpp: Error in binding socket. ErrorNo: %d , ErrorMsg: %s\n", errno,strerror(errno));
		exit(EXIT_FAILURE);
	}


	//try to specify maximum of 3 pending connections for the master socket
	if (listen(iMasterSocket, 3) < 0)
	{
		printf("EventManager.cpp: Error in listening to socket. ErrorNo: %d , ErrorMsg: %s\n", errno,strerror(errno));
		exit(EXIT_FAILURE);
	}

	Server* pServer=new Server(iMasterSocket);
	p_CallBackHandler=pCallBack;
	mServers.insert ( std::pair<int,Server*>(iMasterSocket,pServer) );

	return pServer;

}

Client* EventManager::CreateClient(char* zHost, int iPort,
		SCallBack* pCallBack)
{
	int iSockFD;
	struct sockaddr_in serv_addr;
	struct hostent *poServer;


	/* Create a socket point */
	iSockFD = socket(AF_INET, SOCK_STREAM, 0);
	if (iSockFD < 0)
	{
		printf("EventManager.cpp: Error in opening socket. ErrorNo: %d , ErrorMsg: %s\n", errno,strerror(errno));
		exit(EXIT_FAILURE);
	}
	poServer = gethostbyname(zHost);
	if (poServer == NULL) {
		printf("EventManager.cpp: Error - No such host. ErrorNo: %d , ErrorMsg: %s\n", errno,strerror(errno));
		exit(EXIT_FAILURE);
	}

	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy((char *)poServer->h_addr,
			(char *)&serv_addr.sin_addr.s_addr,
			poServer->h_length);
	serv_addr.sin_port = htons(iPort);

	/* Now connect to the server */
	if (connect(iSockFD,(sockaddr*)&serv_addr,sizeof(serv_addr)) < 0)
	{
		printf("EventManager.cpp: Error in connecting. ErrorNo: %d , ErrorMsg: %s\n", errno,strerror(errno));
		exit(EXIT_FAILURE);
	}

	Client * pClient=new Client(iSockFD);
	mClients.insert ( std::pair<int,Client*>(iSockFD,pClient) );
	return pClient;
}




int EventManager::Run()
{
	char zInputBuffer[MAX_INPUT_BUFFER_SIZE];  //input data buffer
	int iMaxSocketDescriptor, iSocketDescriptor,iSocketActivity,iNewSocket,iAddrlen,iReadValue;
	struct sockaddr_in oAddress;

	 while(true)
		 {
			 //clear the socket set
			 FD_ZERO(&oReadFds);

			 //add STDIN to set
			 FD_SET(STDIN_FILENO, &oReadFds);

			 iMaxSocketDescriptor= 0;
			 //itetrate all the clients
			 std::map<int, Client*>::iterator oClientIter;
			 for (oClientIter = mClients.begin(); oClientIter != mClients.end(); ++oClientIter) 
			 {
				 iSocketDescriptor = oClientIter->second->GetSocket();
				 FD_SET( iSocketDescriptor , &oReadFds);
				 //highest file descriptor number, need it for the select function
				 if(iSocketDescriptor > iMaxSocketDescriptor)
					 iMaxSocketDescriptor = iSocketDescriptor;

			 }

				//iterate the servers 
			 std::map<int, Server*>::iterator  oServerIter;
			 for (oServerIter = mServers.begin(); oServerIter != mServers.end(); ++oServerIter) 
			 {
				 iSocketDescriptor = oServerIter->second->GetSocket();
				 FD_SET( iSocketDescriptor , &oReadFds);
				 //highest file descriptor number, need it for the select function
				 if(iSocketDescriptor > iMaxSocketDescriptor)
					 iMaxSocketDescriptor = iSocketDescriptor;

				 vector<Client*>* pClients=oServerIter->second->GetClients();
				 std:: vector<Client*>::iterator oServerClientIter;
				 for (oServerClientIter = (*pClients).begin(); oServerClientIter != (*pClients).end(); ++oServerClientIter) 
				 {
					 iSocketDescriptor = (*oServerClientIter)->GetSocket();
					 FD_SET( iSocketDescriptor , &oReadFds);
					 //highest file descriptor number, need it for the select function
					 if(iSocketDescriptor > iMaxSocketDescriptor)
						 iMaxSocketDescriptor = iSocketDescriptor;
				 }

			 }
			

			 //wait for an activity on one of the sockets , timeout is NULL , so wait indefinitely
			 iSocketActivity = select( iMaxSocketDescriptor + 1 , &oReadFds , NULL , NULL , NULL);

			 if ((iSocketActivity < 0) && (errno!=EINTR))
			 {
				 printf("EventManager.cpp: Error in select(). ErrorNo: %d , ErrorMsg: %s\n", errno,strerror(errno));
			 }

			 LogDebug("EventManager.cpp: Receiving %s","Message");

			 //check the STDIN
			 if (FD_ISSET(STDIN_FILENO, &oReadFds))
			 {
				 if ((iReadValue = read( STDIN_FILENO , zInputBuffer, MAX_INPUT_BUFFER_SIZE-1)) == 0)
				 {
					 printf("EventManager.cpp: Error in reading from command line. ErrorNo: %d , ErrorMsg: %s\n", errno,strerror(errno));
				 }
				 else{
					 zInputBuffer[iReadValue] = '\0';
					LogDebug("EventManager.cpp: Terminal input: %s",zInputBuffer);
					
					for (oClientIter = mClients.begin(); oClientIter != mClients.end(); ++oClientIter) 
					{

						oClientIter->second->SendMessage(string(zInputBuffer));

					}
				 }
				 
			 }
			 

			 //check the servers
			 
			 for (oServerIter = mServers.begin(); oServerIter != mServers.end(); ++oServerIter) 
			 {

				 iSocketDescriptor = oServerIter->second->GetSocket();
				 //If something happened on a server socket , then its an incoming connection
				 if (FD_ISSET(iSocketDescriptor, &oReadFds))
				 {
					 LogDebug("EventManager.cpp: Receiving Message from %s","Server");
					 if ((iNewSocket = accept(iSocketDescriptor, (struct sockaddr *)&oAddress, (socklen_t*)&iAddrlen))<0)
					 {
						 printf("EventManager.cpp: Error in accepting connection. ErrorNo: %d , ErrorMsg: %s", errno,strerror(errno));
					 }

					 //Create client and notify
					 Client* pClient=new Client(iNewSocket);
					oServerIter->second->AddClient(pClient);
					 p_CallBackHandler->OnConnect(&(*oServerIter->second),pClient);
					

				 }

				 //check for IO operations from the clients of this server
				 vector<Client*>* pClients=oServerIter->second->GetClients();
				 std:: vector<Client*>::iterator oServerClientIter;
				 for (oServerClientIter = (*pClients).begin(); oServerClientIter != (*pClients).end(); ++oServerClientIter) 
				 {
					 
					 iSocketDescriptor = (*oServerClientIter)->GetSocket();
					
					 if (FD_ISSET(iSocketDescriptor, &oReadFds))
					 {
						 LogDebug("EventManager.cpp: Receiving Message from %s","Client");
						 //Check if it was for closing , and also read the incoming message
						 if ((iReadValue = read( iSocketDescriptor , zInputBuffer, MAX_INPUT_BUFFER_SIZE-1)) == 0)
						 {
							 //Somebody disconnected , get his details and print
							 getpeername(iSocketDescriptor, (struct sockaddr*)&oAddress , (socklen_t*)&iAddrlen);
							 LogDebug("%s","---------------------------------------------------------------------");
							 LogDebug("EventManager: Client disconnected, ip %s , port %d",inet_ntoa(oAddress.sin_addr) , ntohs(oAddress.sin_port));

							 p_CallBackHandler->OnDisconnect(&(*oServerIter->second),(*oServerClientIter));
							 

							 //remove from the servers clients as well
							 (*pClients).erase(oServerClientIter);
							 
							 break;


						}
						 else{
							 zInputBuffer[iReadValue] = '\0';

							 LogDebug("%s","---------------------------------------------------------------------");
							 LogDebug("EventManager: Incoming message from ip %s , port %d. Message : %s",inet_ntoa(oAddress.sin_addr) , ntohs(oAddress.sin_port),zInputBuffer);
							 p_CallBackHandler->OnData(&(*oServerIter->second),(*oServerClientIter),string(zInputBuffer));//TODO: use char*
						 }

					 }

				}

			}

			

			 //check for activity in the clients as well
			 
			 for (oClientIter = mClients.begin(); oClientIter != mClients.end(); ++oClientIter) 
			 {
				 iSocketDescriptor = oClientIter->second->GetSocket();
				 if (FD_ISSET(iSocketDescriptor, &oReadFds))
				 {
					LogDebug("EventManager.cpp: Receiving Message from %s","Server");

					//Check if it was for closing , and also read the incoming message
					if ((iReadValue = read( iSocketDescriptor , zInputBuffer, MAX_INPUT_BUFFER_SIZE-1)) == 0)
					{
						
						LogDebug("%s","---------------------------------------------------------------------");
						LogDebug("EventManager: Server disconnected, ip %s , port %d",inet_ntoa(oAddress.sin_addr) , ntohs(oAddress.sin_port));

						p_CallBackHandler->OnDisconnect((*oClientIter).second);

						//remove from the servers clients as well
						mClients.erase(oClientIter);


					}
					else{
						zInputBuffer[iReadValue] = '\0';

						LogDebug("%s","---------------------------------------------------------------------");
						LogDebug("EventManager: Incoming message from Server ip %s , port %d. Message : %s",inet_ntoa(oAddress.sin_addr) , ntohs(oAddress.sin_port),zInputBuffer);
						p_CallBackHandler->OnData((*oClientIter).second,"Server Data");
					}

				 }

			 }


			 

			 



		 }
}
