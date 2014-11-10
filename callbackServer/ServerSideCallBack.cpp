#include "ServerSideCallBack.h"

ServerSideCallBack::ServerSideCallBack(DeliveryController* pDeliveryController)
{
	p_DeliveryController = pDeliveryController;
}

ServerSideCallBack::~ServerSideCallBack()
{
}

void ServerSideCallBack::OnConnect(Server* pServer, Client* pClient)
{
	LogDebug("ServerSideCallBack.cpp : Client connected from socket : %d", pClient->GetSocket());
}

void ServerSideCallBack::OnDisconnect(Server* pServer, Client* pClient)
{
	LogDebug("ServerSideCallBack.cpp : Client disconnected from socket : %d", pClient->GetSocket());
}

void ServerSideCallBack::OnData(Server* pServer, Client* pClient,
		Message* pMessage)
{
	LogDebug("ServerSideCallBack.cpp : Client on socket %d sent : %s", pClient->GetSocket(), pMessage->GetMessage().c_str());
	ChatMessage* pChatMessage = new ChatMessage(pMessage);
	p_DeliveryController->processMessage(pChatMessage);
	delete pChatMessage;
	delete pMessage;
}

void ServerSideCallBack::OnConnect(Client* pClient)
{
	LogDebug("ServerSideCallBack.cpp : Invalid callback - %s","Connect");
}

void ServerSideCallBack::OnDisconnect(Client* pClient)
{
	LogDebug("ServerSideCallBack.cpp : Invalid callback - %s","Disconnect");
}

void ServerSideCallBack::OnData(Client* pClient, Message* pMessage)
{
	LogDebug("ServerSideCallBack.cpp : Invalid callback - %s : %s","Data", pMessage->GetMessage().c_str());
	delete pMessage;
}
