/*
 * SCallBack.h
 *
 *  Created on: Oct 13, 2014
 *      Author: ishan
 */

#ifndef SCALLBACK_H_
#define SCALLBACK_H_

#include "Utils.h"
#include "Server.h"
#include "Client.h"


class SCallBack {
public:
	SCallBack();
	virtual ~SCallBack();

	void OnConnect(Server* pServer, Client* pClient);
	void OnDisconnect(Server* pServer, Client* pClient);
	void OnData(Server* pServer, Client* pClient, string sData);

	void OnConnect(Client* pClient);
	void OnDisconnect(Client* pClient);
	void OnData(Client* pClient, string sData);

private:
	

};

#endif /* SCALLBACK_H_ */
