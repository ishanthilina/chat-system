/*
 * Client.h
 *
 *  Created on: Oct 13, 2014
 *      Author: ishan
 */

#ifndef _CLIENT_HEADER_
#define _CLIENT_HEADER_

class Message;
class Server;

#include <string>
 #include <sys/socket.h>
#include <netdb.h>
#include <sys/types.h>
#include <unistd.h>   //defines read
#include <errno.h>

#include "Utils.h"
#include "Message.h"
#include "SCallBack.h"
#include "Server.h"

#define MAX_INPUT_BUFFER_SIZE 1025


using namespace std;

class Client {
public:
	//when creating a server side client
	Client(int iSocketFd, SCallBack* pSCallBack, Server* pServer);
	//when creating a client side client
	Client(int iSocketFd, SCallBack* pSCallBack);
	virtual ~Client();

	int SendMessage(Message* pMessage);
	int GetSocket();
	//return value denotes whether the event was a client disconnect or not
	//if return value = 1 -> Client disconnect
	int ProcessClientEvent(); 
	
private:
	int i_SocketFd;
	SCallBack* p_SCallBack;
	Message* p_Buffer;
	bool b_IsServerSideClient;
	Server* p_Server;

	void FillBuffer();


	char zInputBuffer[MAX_INPUT_BUFFER_SIZE];
};

#endif /* _CLIENT_HEADER_ */
