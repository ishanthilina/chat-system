#ifndef _SERVER_SIDE_CALL_BACK_HEADER
#define _SERVER_SIDE_CALL_BACK_HEADER

#include "SCallBack.h"

class ServerSideCallBack : SCallBack {
public:
	ServerSideCallBack();
	virtual ~ServerSideCallBack();

	void OnConnect(Server* pServer, Client* pClient);
	void OnDisconnect(Server* pServer, Client* pClient);
	void OnData(Server* pServer, Client* pClient, string sData);

	void OnConnect(Client* pClient);
	void OnDisconnect(Client* pClient);
	void OnData(Client* pClient, string sData);

private:


};


#endif	//_SERVER_SIDE_CALL_BACK_HEADER

