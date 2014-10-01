#ifndef _DELIVERY_CONTROLLER_HEADER_
#define _DELIVERY_CONTROLLER_HEADER_

#include "Logger.h"
#include "Server.h"
#include "Message.h"

using namespace std;
class DeliveryController
{
public:
	DeliveryController(Logger * o_Logger, Server * o_Server);
	int processMessage(Message * o_Message);

	Logger * o_Logger;
	Server * o_Server;
protected:
private:
};

#endif