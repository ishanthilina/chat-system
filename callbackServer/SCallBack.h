/*
 * SCallBack.h
 *
 *  Created on: Oct 13, 2014
 *      Author: ishan
 */

#ifndef _SCALLBACK_HEADER_
#define _SCALLBACK_HEADER_

#include "Utils.h"
#include "Server.h"
#include "Client.h"


class SCallBack {
public:

	virtual void OnConnect(Server* pServer, Client* pClient)=0;
	virtual void OnDisconnect(Server* pServer, Client* pClient)=0;
	virtual void OnData(Server* pServer, Client* pClient, string sData)=0;

	virtual void OnConnect(Client* pClient)=0;
	virtual void OnDisconnect(Client* pClient)=0;
	virtual void OnData(Client* pClient, string sData)=0;

private:
	

};

#endif /* _SCALLBACK_HEADER_ */
