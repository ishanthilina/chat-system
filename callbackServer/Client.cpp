/*
 * Client.cpp
 *
 *  Created on: Oct 13, 2014
 *      Author: ishan
 */

#include "Client.h"

Client::Client(int iSocketFd, SCallBack* pSCallBack) {
	i_SocketFd=iSocketFd;
	p_SCallBack=pSCallBack;
	b_IsServerSideClient = false;

}

Client::Client( int iSocketFd, SCallBack* pSCallBack, Server* pServer )
{
	i_SocketFd=iSocketFd;
	p_SCallBack=pSCallBack;
	p_Server=pServer;
	b_IsServerSideClient = true;
}

Client::~Client() {

}

int Client::GetSocket()
{
	return i_SocketFd;
}

int Client::SendMessage(Message* pMessage)
{
	string sMessage= pMessage->GetEncodedMessage();
	LogDebug("Client.cpp: Sending to socket %d : %s",i_SocketFd,sMessage.c_str());

	int iValWritten=0;
	if ((iValWritten = write( i_SocketFd , sMessage.c_str(), sMessage.length())) == 0)//TODO: handle the buffering of the server socket.
	{
		LogDebug("Client.cpp: %s","Error writing to socket");

	}
	return iValWritten;
}

int Client::ProcessClientEvent()
{
	int iReadValue=-1, iAddrlen=0;
	struct sockaddr_in oAddress;
	LogDebug("Client.cpp: Receiving Message from client socket %d",i_SocketFd);
	//Check if it was for closing , and also read the incoming message
	if ((iReadValue = read( i_SocketFd , zInputBuffer, MAX_INPUT_BUFFER_SIZE-1)) == 0)
	{
		//Somebody disconnected , get his details and print
		getpeername(i_SocketFd, (struct sockaddr*)&oAddress , (socklen_t*)&iAddrlen);
		LogDebug("%s","---------------------------------------------------------------------");
		LogDebug("Client.cpp: Client disconnected, ip %s , port %d",inet_ntoa(oAddress.sin_addr) , ntohs(oAddress.sin_port));

		p_SCallBack->OnDisconnect(p_Server,this);


		//remove from the servers clients as well
		//(*pClients).erase(oServerClientIter);

		return 1;


	}
	else{
		zInputBuffer[iReadValue] = '\0';

		LogDebug("%s","---------------------------------------------------------------------");
		LogDebug("Client.cpp: Incoming message from ip %s , port %d. Message : %s",inet_ntoa(oAddress.sin_addr) , ntohs(oAddress.sin_port),zInputBuffer);
		
		string sNewMessage = string(zInputBuffer); //TODO: use char*

		//remove any null characters or new lines at the end of the string
		if(sNewMessage.compare(sNewMessage.length()-1,1,"\n") ==0)
		{
			sNewMessage=sNewMessage.substr(0,sNewMessage.size()-1);
		}
		if(sNewMessage.compare(sNewMessage.length()-1,1,"\r") ==0)
		{
			sNewMessage=sNewMessage.substr(0,sNewMessage.size()-1);
		}

		//check if a message is already being built for this client
		if (p_Buffer !=NULL)
		{
			p_Buffer->FillMessage(sNewMessage);
			//if the message is complete now
			if(p_Buffer->IsMessageComplete())
			{
				LogDebug("Client.cpp: Message from client socket %d complete",i_SocketFd); 
				p_SCallBack->OnData(p_Server,this,p_Buffer);
				
				//delete pMessage;
				delete p_Buffer;//TODO: better be handled at the processing party - remove from this layer
				return 0;

			}

			else if(!p_Buffer->IsValidMessage())
			{
				LogDebug("Client.cpp: Message from client socket %d is invalid, deleting.",i_SocketFd); 
				//remove the message 
				delete p_Buffer;
				return 0;

			}
		}
		else
		{
			LogDebug("Client.cpp: Creating new message from client socket %d",i_SocketFd);
			p_Buffer =  new Message(sNewMessage, p_Server, this);

			//only do anything if this is a valid message
			if(p_Buffer->IsValidMessage())
			{
				LogDebug("Client.cpp: Created a valid new message from client socket %d",i_SocketFd);
				//check if the message is completely built
				if(p_Buffer->IsMessageComplete())
				{
					LogDebug("Client.cpp: New message from client socket %d is complete.",i_SocketFd);

					//p_DeliveryController->processMessage(oBufferedMsg);
					p_SCallBack->OnData(p_Server,this,p_Buffer);
					delete p_Buffer;
					return 0;
				}

				//p_BufferredMessages->insert(pair<Client*, Message*>(pClient,oBufferedMsg));
			}
			else	//if invalid message
			{
				LogDebug("Client.cpp: New message from client socket %d is invalid.",i_SocketFd);
				delete p_Buffer;
			}
		}


	}

	return 0;
}



