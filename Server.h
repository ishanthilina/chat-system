#ifndef _SERVER_HEADER_
#define _SERVER_HEADER_

class DeliveryController;

#include <string>
#include <iostream>
#include <stdio.h>	//defines perror
#include <stdlib.h>	//defines  exit and EXIT_FAILURE
#include <sys/time.h> //FD_SET, FD_ISSET, FD_ZERO macros
#include <errno.h>

//#include <arpa/inet.h>    //close
//#include <sys/types.h>
//#include <sys/socket.h>
//#include <netinet/in.h>
#include <unistd.h>   //defines read

#include <vector>
#include "DeliveryController.h"
#include "MessageFactory.h"

using namespace std;

class Server
{
public:
	Server(MessageFactory * p_MsgFactory,DeliveryController * p_MsgProcessor);
	int SendMessage(string s_Message, int i_socket);
	int Disconnect(int i_Socket);
	int AddClient(Client * o_Client);
	bool RemoveClient(Client * o_Client);
	//Client GetAllClients();
	void RunServer();

	
protected:
private:
	MessageFactory * p_MsgFactory;
	DeliveryController * p_MsgProcessor;
	vector<Client*> * o_Clients;
	vector<int*> * o_ClientDescriptors;
};

#endif	//_SERVER_HEADER_
