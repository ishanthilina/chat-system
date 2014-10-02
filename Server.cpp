#include "Server.h"


Server::Server( MessageFactory * p_MsgFactory,DeliveryController * p_MsgProcessor )
{
	this->p_MsgFactory=p_MsgFactory;
	this->p_MsgProcessor=p_MsgProcessor;
	vector = new vector<string>;
}

void Server::RunServer()
{

	string testMsg = "LIN;ishanthilina";
	//string testMsg = "P2P;ishanthilina,thisarar;my Message";
	//string testMsg = "DDD;ishanthilina,thisarar;my Message";

	Message * oMmessage=p_MsgFactory->createMessage(1,testMsg);
	p_MsgProcessor->processMessage(oMmessage);
	

	cout<<"Server:: "<<oMmessage->GetMessage()<<endl;

	delete oMmessage;
}

int Server::AddClient( Client * o_Client )
{
	cout<<"SERVER:: Add Client - "<<o_Client->GetLogName();

}

int main(){

	MessageFactory * pFactory = new MessageFactory();
	Logger * pLogger = new Logger();
	DeliveryController * pController = new DeliveryController(pLogger);
	Server * pServer=new Server(pFactory,pController);
	pController->setServer(pServer);
	pServer->RunServer();

	delete pFactory;
	delete pLogger;
	delete pController;
	delete pServer;
	//cout<<"main"<<endl;
}
