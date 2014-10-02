#ifndef _DELIVERY_CONTROLLER_HEADER_
#define _DELIVERY_CONTROLLER_HEADER_

class Server;

#include "Logger.h"
#include "Server.h"
#include "Message.h"
#include "Client.h"

using namespace std;
class DeliveryController
{
public:
	DeliveryController(Logger * o_Logger);
	int processMessage(Message * o_Message);
	void setServer(Server*);

	
protected:
private:
	Logger * o_Logger;
	Server * o_Server;
};

#endif