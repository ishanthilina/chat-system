#include "UserRegistry.h"
#include "MessageFactory.h"
#include "DeliveryController.h"
//#include "MessageBuffer.h"
#include "SCallBack.h"
#include "ServerSideCallBack.h"
#include "EventManager.h"

int main()
{

	UserRegistry* pUserRegistry = new UserRegistry();
	MessageFactory* pMessageFactory = new MessageFactory(pUserRegistry);

	DeliveryController* pDeliveryController = new DeliveryController(pUserRegistry,pMessageFactory);

	//MessageBuffer* pMessageBuffer = new MessageBuffer(pDeliveryController);

	ServerSideCallBack* pServerSideCallBack = new ServerSideCallBack(pDeliveryController);
	EventManager* pEventManager = new EventManager();

	Server* pServer = pEventManager->CreateServer(8888, pServerSideCallBack);
	pEventManager->Run();

	delete pUserRegistry;
	delete pMessageFactory;
	delete pDeliveryController;
	//delete pMessageBuffer;
	delete pServerSideCallBack;
	delete pEventManager;
	delete pServer;


	return 0;
}
