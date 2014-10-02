#ifndef _SERVER_HEADER_
#define _SERVER_HEADER_

class DeliveryController;

#include <string>
#include <iostream>
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
	vector<string> * clients;
};

#endif