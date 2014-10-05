/*
 * EventHandler.cpp
 *
 *  Created on: Oct 5, 2014
 *      Author: ishan
 */

#include "EventHandler.h"

EventHandler::EventHandler(SocketOperator * oNetworkSocketOp) {
	this->isLoggedIn=false;
	this->o_NetworkSocketOp=oNetworkSocketOp;

}

void EventHandler::HandleEvent(string sMessage)
{
	//if not logged in consider as a login message
	if(!isLoggedIn)
	{
		//std::string username;
		//std::cout<<"Please Enter UserName: "<<std::endl;
		//	std::cin>>username;
			std::string loginMessage="LIN;";
			loginMessage.append(sMessage);
		//
			char *cstr = new char[loginMessage.length() + 1];
			strcpy(cstr, loginMessage.c_str());
		//
			o_NetworkSocketOp->WriteToSocket(cstr,loginMessage.length());

			//o_NetworkSocketOp->ReadFromSocket(cstr,14);
			//std::cout<<cstr;
			//delete [] cstr;
			isLoggedIn=true;

		// o_NetworkSocketOp->WriteToSocket()
	}
	else		//if already logged in
	{
		std::string message="PTP;";
		message.append(sMessage);
		//
		char *cstr = new char[message.length() + 1];
		strcpy(cstr, message.c_str());
		//
		o_NetworkSocketOp->WriteToSocket(cstr,message.length());

		//o_NetworkSocketOp->ReadFromSocket(cstr,14);
		//std::cout<<cstr;
		//delete [] cstr;
	}
}

EventHandler::~EventHandler() {
	// TODO Auto-generated destructor stub
}

