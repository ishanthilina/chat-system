/*
 * EventListener.cpp
 *
 *  Created on: Oct 5, 2014
 *      Author: ishan
 */

#include "EventListener.h"

EventListener::EventListener(int sockfd,SocketOperator * oNetSockOperator, SocketOperator * oTerminalSocketOperator,MessageProcessor * oMsgProcessor,MessageFactory * oMessageFactory) {
	this->sockfd=sockfd;
	this->o_NetSockOperator=oNetSockOperator;
	this->o_TerminalSocketOperator=oTerminalSocketOperator;
	this->o_MessageProcessor=oMsgProcessor;
	this->o_MessageFactory=oMessageFactory;

}

int EventListener::Listen(){

	//set of socket descriptors
		fd_set readfds;

		char buffer[MAX_INPUT_BUFFER_SIZE+1];

		int activity;

		bool bRunLoop=true;

	while(bRunLoop){

		LogDebug("EventListener.cpp -  : %s","Clearing");

		//clear the socket set
		FD_ZERO(&readfds);

		//add server socket to set
		FD_SET(sockfd, &readfds);

		//add stdin to set
		FD_SET(STDIN_FILENO, &readfds);

		int max_sd= STDIN_FILENO > sockfd ? STDIN_FILENO : sockfd;

		

		activity = select( max_sd + 1 , &readfds , NULL , NULL , NULL);

		if ((activity < 0) && (errno!=EINTR))
		{
			printf("select error");
			return 2;
		}

		if (FD_ISSET(sockfd, &readfds)) {

			LogDebug("%s","-----------------------------------------------------------------------------");
			LogDebug("Incoming message from %s","server");
			memset(buffer, 0, MAX_INPUT_BUFFER_SIZE);
			int iReadValue=o_NetSockOperator->ReadFromSocket(buffer,MAX_INPUT_BUFFER_SIZE);
			if(!iReadValue){
				o_MessageProcessor->SetClientState(LOGIN_USERNAME_PENDING);
				close(sockfd);
				LogDebug("EventListener.cpp - Server %s","Disconnected");
				return 2;
				//bRunLoop=false;

			}

			buffer[iReadValue]='\0';

			LogDebug("EventListener.cpp - Message Size : %d",iReadValue);
			
			std::string message(buffer);
			LogDebug("EventListener.cpp - Message : %s",message.c_str());

			o_MessageFactory->CreateMessage(message.substr(0,message.find_first_of('\n')));

		}

		else if(FD_ISSET(STDIN_FILENO, &readfds)){

			LogDebug("%s","-----------------------------------------------------------------------------");
			memset(buffer, 0, MAX_INPUT_BUFFER_SIZE);
			o_TerminalSocketOperator->ReadFromSocket(buffer,MAX_INPUT_BUFFER_SIZE);

			std::string message(buffer);
			LogDebug("EventListener.cpp - Message : %s",message.c_str());
			o_MessageProcessor->ProcessUserInput(message.substr(0,message.find_first_of('\n')));

		}
		else{
			LogDebug("EventListener.cpp - Error-Incoming message from : %s"," unknown source");
		}

	}

	return 0;
}

EventListener::~EventListener() {
	// TODO Auto-generated destructor stub
}

