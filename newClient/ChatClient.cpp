/*
 * ChatClient.cpp
 *
 *  Created on: Oct 5, 2014
 *      Author: ishan
 */

#include "ChatClient.h"


ChatClient::ChatClient() {

}

int ChatClient::StartClient() {
	
	int sockfd=this->Connect();
	bool bShouldRun=true;
	do 
	{
		cout<<"Run"<<endl;
		//create the socket operators
		SocketOperator * oNetSockOperator=new SocketOperator(sockfd);
		SocketOperator * oTerminalSocketOperator=new SocketOperator(STDIN_FILENO);


		MessageParser * oMsgParser=new MessageParser();
		ScreenWriter * oScreenWriter = new ScreenWriter();
		MessageProcessor * oEventHndler=new MessageProcessor(oMsgParser,oNetSockOperator,oTerminalSocketOperator,oScreenWriter);

		MessageFactory * oMessageFactory = new MessageFactory(oEventHndler);

		//event listener
		EventListener * eventListener=new EventListener(sockfd,oNetSockOperator,oTerminalSocketOperator,oEventHndler,oMessageFactory);
		int iExitStatus=eventListener->Listen();
		cout<<"BEFORE"<<endl;
		while (iExitStatus!=2)
		{
			bShouldRun=false;

		}



		delete oNetSockOperator;
		delete oTerminalSocketOperator;
		delete eventListener;
		delete oMessageFactory;
		delete oEventHndler;
		delete oMsgParser;
		delete oScreenWriter;

		//wait before reconnecting
		usleep(1000000);	//sleep 1 second
	} while (bShouldRun);

	

	return 0;


}

ChatClient::~ChatClient() {
	// TODO Auto-generated destructor stub
}

int ChatClient::Connect()
{
	int sockfd, portno, n;
	struct sockaddr_in serv_addr;
	struct hostent *server;

	portno = 8888;
	/* Create a socket point */
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
	{
		perror("ERROR opening socket");
		return -1;
	}
	server = gethostbyname("127.0.0.1");
	if (server == NULL) {
		fprintf(stderr,"ERROR, no such host\n");
		return -1;
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
		return -1;
	}

	return sockfd;
}

int main()
{
	ChatClient * client=new ChatClient();
	client->StartClient();
	delete client;
	return 0;
}

