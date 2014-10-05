/*
 * ChatClient.cpp
 *
 *  Created on: Oct 5, 2014
 *      Author: ishan
 */

#include "ChatClient.h"

ChatClient::ChatClient() {
	// TODO Auto-generated constructor stub

}



int ChatClient::StartClient() {
	int sockfd, portno, n;
	struct sockaddr_in serv_addr;
	struct hostent *server;




	//,valread;

//	if (argc < 3) {
//		fprintf(stderr,"usage %s hostname port\n", argv[0]);
//		return 0;
//	}
	portno = 8888;
	/* Create a socket point */
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
	{
		perror("ERROR opening socket");
		return 1;
	}
	server = gethostbyname("127.0.0.1");
	if (server == NULL) {
		fprintf(stderr,"ERROR, no such host\n");
		return 0;
	}

	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy((char *)server->h_addr,
			(char *)&serv_addr.sin_addr.s_addr,
			server->h_length);
	serv_addr.sin_port = htons(portno);

	/* Now connect to the server */
	if (connect(sockfd,(sockaddr*)&serv_addr,sizeof(serv_addr)) < 0)
	{
		perror("ERROR connecting");
		return 1;
	}

	//create the socket operators
	SocketOperator * oNetSockOperator=new SocketOperator(sockfd);
	SocketOperator * oTerminalSocketOperator=new SocketOperator(STDIN_FILENO);

	//event listener
	EventListener * eventListener=new EventListener(sockfd,oNetSockOperator,oTerminalSocketOperator);
	eventListener->Listen();


	delete oNetSockOperator;
	delete oTerminalSocketOperator;
	delete eventListener;

	return 0;


}

ChatClient::~ChatClient() {
	// TODO Auto-generated destructor stub
}

int main()
{
	ChatClient * client=new ChatClient();
	client->StartClient();
	return 0;
}

