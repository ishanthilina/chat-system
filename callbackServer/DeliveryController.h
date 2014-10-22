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
#include "Server.h"
#include "UserRegistry.h"
#include "Message.h"
#include "Logger.h"
#include "User.h"
#include "MessageFactory.h"
#include "Utils.h"

using namespace std;

class DeliveryController {
public:
	DeliveryController(UserRegistry * pUserRegistry, MessageFactory* pMessageFactory);
	void processMessage( Message * oMessage );
	virtual ~DeliveryController();
private:
	UserRegistry * p_UserRegistry;
	Logger * p_Logger;
	MessageFactory* p_MessageFactory;

};

#endif /* DELIVERYCONTROLLER_H_ */
