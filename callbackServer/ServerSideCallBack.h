#ifndef _SERVER_SIDE_CALL_BACK_HEADER
#define _SERVER_SIDE_CALL_BACK_HEADER

#include "SCallBack.h"
#include "Utils.h"
#include "DeliveryController.h"

class ServerSideCallBack : public SCallBack {
public:
	ServerSideCallBack(DeliveryController* pDeliveryController);
	virtual ~ServerSideCallBack();

	void OnConnect(Server* pServer, Client* pClient);
	void OnDisconnect(Server* pServer, Client* pClient);
	void OnData(Server* pServer, Client* pClient, Message* pMessage);

	void OnConnect(Client* pClient);
	void OnDisconnect(Client* pClient);
	void OnData(Client* pClient, Message* pMessage);

private:
	DeliveryController* p_DeliveryController;


};


#endif	//_SERVER_SIDE_CALL_BACK_HEADER

