/*
 * DeliveryController.h
 *
 *  Created on: Oct 8, 2014
 *      Author: ishan
 */

#ifndef DELIVERYCONTROLLER_H_
#define DELIVERYCONTROLLER_H_

#include <string>

#include "Client.h"
#include "ClientRegistry.h"
#include "Message.h"
#include "Logger.h"
#include "SocketOperator.h"
#include "StringMessageBuilder.h"

using namespace std;

class DeliveryController {
public:
	DeliveryController(ClientRegistry * pClientRegistry,SocketOperator * pSocketOperator);
	void processMessage( Message * o_Message );
	virtual ~DeliveryController();
private:
	ClientRegistry * p_ClientRegistry;
	SocketOperator * p_SocketOperator;
	Logger * p_Logger;
	StringMessageBuilder * p_StringMsgBuilder;
};

#endif /* DELIVERYCONTROLLER_H_ */
