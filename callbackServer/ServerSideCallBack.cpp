#include "ServerSideCallBack.h"

ServerSideCallBack::ServerSideCallBack(MessageBuffer* pMessageBuffer)
{
	p_MessageBuffer = pMessageBuffer;
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
		string sData)
{
	LogDebug("ServerSideCallBack.cpp : Client on socket %d sent : %s", pClient->GetSocket(), sData.c_str());
	p_MessageBuffer->CreateMessage(pServer, pClient, sData);
}

void ServerSideCallBack::OnConnect(Client* pClient)
{
	LogDebug("ServerSideCallBack.cpp : Invalid callback - %s","Connect");
}

void ServerSideCallBack::OnDisconnect(Client* pClient)
{
	LogDebug("ServerSideCallBack.cpp : Invalid callback - %s","Disconnect");
}

void ServerSideCallBack::OnData(Client* pClient, string sData)
{
	LogDebug("ServerSideCallBack.cpp : Invalid callback - %s : %s","Data", sData.c_str());
}
