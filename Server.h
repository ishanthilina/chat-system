#ifndef _SERVER_HEADER_
#define _SERVER_HEADER_

#include <string>
#include <iostream>
#include "DeliveryController.h"
#include "MessageFactory.h"

using namespace std;

class Server
{
public:
	Server(MessageFactory * o_MsgFactory,DeliveryController * o_MsgProcessor);
	void SendMessage(string s_Message, int i_socket);
	void Disconnect(int i_Socket);
	void AddClient(Client * o_Client);
	bool RemoveClient(Client * o_Client);
	//Client GetAllClients();
	void RunServer();

	MessageFactory * o_MsgFactory;
	DeliveryController * o_MsgProcessor;
protected:
private:
};

#endif