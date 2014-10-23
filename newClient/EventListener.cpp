/*
 * EventListener.cpp
 *
 *  Created on: Oct 5, 2014
 *      Author: ishan
 */

#include "EventListener.h"

EventListener::EventListener(int iSockFD,SocketOperator * pNetSockOperator, SocketOperator * pTerminalSocketOperator,MessageProcessor * pMsgProcessor,MessageFactory * pMessageFactory) 
{
	this->i_SockFD=iSockFD;
	this->p_NetSockOperator=pNetSockOperator;
	this->p_TerminalSocketOperator=pTerminalSocketOperator;
	this->p_MessageProcessor=pMsgProcessor;
	this->p_MessageFactory=pMessageFactory;

}

int EventListener::Listen()
{

	//set of socket descriptors
		fd_set sReadFDs;

		char zBuffer[MAX_INPUT_BUFFER_SIZE+1];

		int iActivity;

		bool bRunLoop=true;

	while(bRunLoop)
	{

		LogDebug("EventListener.cpp -  : %s","Clearing");

		//clear the socket set
		FD_ZERO(&sReadFDs);

		//add server socket to set
		FD_SET(i_SockFD, &sReadFDs);

		//add stdin to set
		FD_SET(STDIN_FILENO, &sReadFDs);

		int max_sd= STDIN_FILENO > i_SockFD ? STDIN_FILENO : i_SockFD;

		

		iActivity = select( max_sd + 1 , &sReadFDs , NULL , NULL , NULL);

		if ((iActivity < 0) && (errno!=EINTR))
		{
			printf("select error");
			return 2;
		}

		if (FD_ISSET(i_SockFD, &sReadFDs)) 
		{

			LogDebug("%s","-----------------------------------------------------------------------------");
			LogDebug("Incoming message from %s","server");
			memset(zBuffer, 0, MAX_INPUT_BUFFER_SIZE);
			int iReadValue=p_NetSockOperator->ReadFromSocket(zBuffer,MAX_INPUT_BUFFER_SIZE);
			if(!iReadValue){
				p_MessageProcessor->SetClientState(LOGIN_USERNAME_PENDING);
				close(i_SockFD);
				LogDebug("EventListener.cpp - Server %s","Disconnected");
				return 2;

			}

			zBuffer[iReadValue]='\0';

			LogDebug("EventListener.cpp - Message Size : %d",iReadValue);
			
			std::string message(zBuffer);
			LogDebug("EventListener.cpp - Message : %s",message.c_str());

			p_MessageFactory->CreateMessage(message.substr(0,message.find_first_of('\n')));

		}

		else if(FD_ISSET(STDIN_FILENO, &sReadFDs))
		{

			LogDebug("%s","-----------------------------------------------------------------------------");
			memset(zBuffer, 0, MAX_INPUT_BUFFER_SIZE);
			p_TerminalSocketOperator->ReadFromSocket(zBuffer,MAX_INPUT_BUFFER_SIZE);

			std::string message(zBuffer);
			LogDebug("EventListener.cpp - Message : %s",message.c_str());
			p_MessageProcessor->ProcessUserInput(message.substr(0,message.find_first_of('\n')));

		}
		else
		{
			LogDebug("EventListener.cpp - Error-Incoming message from : %s"," unknown source");
		}

	}

	return 0;
}

EventListener::~EventListener() 
{
	
}

