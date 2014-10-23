/*
 * ChatClient.cpp
 *
 *  Created on: Oct 5, 2014
 *      Author: ishan
 */

#include "ChatClient.h"


ChatClient::ChatClient() 
{

}

int ChatClient::StartClient() {
	
	
	bool bShouldRun=true;
	do 
	{
		int iSockFD=this->Connect();

		if(iSockFD <0)
		{
			//wait before reconnecting
			usleep(SLEEP_TIME);	
			continue;
		}

		
		//create the socket operators
		SocketOperator * pNetSockOperator=new SocketOperator(iSockFD);
		SocketOperator * pTerminalSocketOperator=new SocketOperator(STDIN_FILENO);


		MessageParser * pMsgParser=new MessageParser();
		ScreenWriter * pScreenWriter = new ScreenWriter();
		MessageProcessor * pEventHndler=new MessageProcessor(pMsgParser,pNetSockOperator,pTerminalSocketOperator,pScreenWriter);

		MessageFactory * pMessageFactory = new MessageFactory(pEventHndler);

		//event listener
		EventListener * pEventListener=new EventListener(iSockFD,pNetSockOperator,pTerminalSocketOperator,pEventHndler,pMessageFactory);
		int iExitStatus=pEventListener->Listen();
		//if not a server disconnect exit
		if (iExitStatus!=2)
		{
			bShouldRun=false;

		}



		delete pNetSockOperator;
		delete pTerminalSocketOperator;
		delete pEventListener;
		delete pMessageFactory;
		delete pEventHndler;
		delete pMsgParser;
		delete pScreenWriter;

		//wait before reconnecting
		usleep(SLEEP_TIME);	
	} while (bShouldRun);

	

	return 0;


}

ChatClient::~ChatClient() 
{
}

int ChatClient::Connect()
{
	int iSockFD, iPortNo;
	struct sockaddr_in sServAddr;
	struct hostent *psServer;

	iPortNo = 8888;
	/* Create a socket point */
	iSockFD = socket(AF_INET, SOCK_STREAM, 0);
	if (iSockFD < 0)
	{
		perror("ERROR opening socket");
		return -1;
	}
	psServer = gethostbyname("127.0.0.1");
	if (psServer == NULL) {
		fprintf(stderr,"ERROR, no such host\n");
		return -1;
	}

	bzero((char *) &sServAddr, sizeof(sServAddr));
	sServAddr.sin_family = AF_INET;
	bcopy((char *)psServer->h_addr,
		(char *)&sServAddr.sin_addr.s_addr,
		psServer->h_length);
	sServAddr.sin_port = htons(iPortNo);

	/* Now connect to the server */
	if (connect(iSockFD,(sockaddr*)&sServAddr,sizeof(sServAddr)) < 0)
	{
		perror("ERROR connecting");
		return -1;
	}

	return iSockFD;
}

int main()
{
	ChatClient * client=new ChatClient();
	client->StartClient();
	delete client;
	return 0;
}

