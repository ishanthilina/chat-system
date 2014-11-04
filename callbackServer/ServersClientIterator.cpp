#include "ServersClientIterator.h"

ServersClientIterator::ServersClientIterator( const Server* pServer )
{
	p_Clients = pServer->p_Clients;
	oServerClientIter = p_Clients->begin();
}

Client* ServersClientIterator::First()
{
	oServerClientIter = p_Clients->begin();
}

void ServersClientIterator::Next()
{
	if (oServerClientIter != p_Clients->end())
	{
		++oServerClientIter;
	}
}

bool ServersClientIterator::IsDone()
{
	return oServerClientIter == p_Clients->end();
}

Client* ServersClientIterator::CurrentItem()
{
	return (*oServerClientIter);
}

void ServersClientIterator::EraseItem()
{
	delete (*oServerClientIter);
	p_Clients->erase((*oServerClientIter));
	//reset the iterator as well
	oServerClientIter = p_Clients->begin();
}
