/*
 * EventHandler.h
 *
 *  Created on: Oct 5, 2014
 *      Author: ishan
 */

#ifndef EVENTHANDLER_H_
#define EVENTHANDLER_H_

#include <string>

#include "SocketOperator.h"

using namespace std;

class EventHandler {
public:
	EventHandler(SocketOperator * oNetworkSocketOp);
	void HandleEvent(string sMessage);
	virtual ~EventHandler();
private:
	bool isLoggedIn;
	SocketOperator * o_NetworkSocketOp;
};

#endif /* EVENTHANDLER_H_ */
