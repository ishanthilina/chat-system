/*
 * EventListener.cpp
 *
 *  Created on: Oct 5, 2014
 *      Author: ishan
 */

#include "EventListener.h"

EventListener::EventListener(int sockfd,SocketOperator * oNetSockOperator, SocketOperator * oTerminalSocketOperator,MessageProcessor * oMsgProcessor) {
	this->sockfd=sockfd;
	this->o_NetSockOperator=oNetSockOperator;
	this->o_TerminalSocketOperator=oTerminalSocketOperator;
	this->o_MessageProcessor=oMsgProcessor;

}

int EventListener::Listen(){

	//set of socket descriptors
		fd_set readfds;

		char buffer[256];

		int activity;

	while(1){

		//clear the socket set
		FD_ZERO(&readfds);

		//add server socket to set
		FD_SET(sockfd, &readfds);

		//add stdin to set
		FD_SET(STDIN_FILENO, &readfds);

		int max_sd= STDIN_FILENO > sockfd ? STDIN_FILENO : sockfd;
		//printf("STDIN_FILENO : %d , sockfd : %d , max_sd : %d ",STDIN_FILENO,sockfd,max_sd);

		activity = select( max_sd + 1 , &readfds , NULL , NULL , NULL);

		if ((activity < 0) && (errno!=EINTR))
		{
			printf("select error");
		}

		if (FD_ISSET(sockfd, &readfds)) {
			printf("Incoming message: ");

//			if ((valread = read( sockfd , buffer, 255)) == 0)
//			{
//				printf("Server Disconnected");
//				return 0;
//			}
//			else{
//				//std::string message(buffer);
//				//int n=message.find_first_of("\n");
//				//printf("s: %s\n",message.substr(0,n));
//				std::cout<<buffer;
//			}
			int status=o_NetSockOperator->ReadFromSocket(buffer,255);
			if(status){
				printf("Server Disconnected");
				return 0;
			}

			std::cout<<buffer<<endl;

		}

		else if(FD_ISSET(STDIN_FILENO, &readfds)){
			//printf("Console input: ");

//			if ((valread = read( STDIN_FILENO , buffer, 255)) == 0)
//			{
//				printf("O.o");
//				return 0;
//			}
//			else{
//				//printf("c: %s\n",buffer);
//
//				std::string message(buffer);
//
//				int n;
//				n = write(sockfd,buffer,message.find_first_of("\n"));
//
//				if (n < 0)
//				{
//					perror("ERROR writing to socket");
//
//					return 0;
//				}
//
//			}

			o_TerminalSocketOperator->ReadFromSocket(buffer,255);

			std::string message(buffer);
			o_MessageProcessor->ProcessUserInput(message.substr(0,message.find_first_of('\n')));
			cout<<"CMD event handled"<<endl;


			//oNetSockOperator->WriteToSocket(buffer,message.find_first_of("\n"));



//			int n;
//			n = write(sockfd,buffer,message.find_first_of("\n"));
//
//			if (n < 0)
//			{
//				perror("ERROR writing to socket");
//
//				return 0;
//			}

		}
		else{
			printf("Error");
		}



	}

	return 0;
}

EventListener::~EventListener() {
	// TODO Auto-generated destructor stub
}

