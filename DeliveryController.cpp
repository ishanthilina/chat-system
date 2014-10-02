#include "DeliveryController.h"

DeliveryController::DeliveryController( Logger * o_Logger)
{
	this->o_Logger = o_Logger;
	
}

int DeliveryController::processMessage( Message * o_Message )
{
	cout<<"Processing message: "<< o_Message->GetMessage()<<endl;

	//login message
	if(o_Message->GetMessageType()==LOGIN)
	{
		cout<<"DeliveryController::login msg"<<endl;

		Client oClient = new Client(o_Message->GetMessage(),o_Message->GetSenderSocket(),)





	}

	return 0;

}

void DeliveryController::setServer(Server * o_Server)
{
	this->o_Server = o_Server;
}
