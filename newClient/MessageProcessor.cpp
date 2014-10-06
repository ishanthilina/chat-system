#include "MessageProcessor.h"

void MessageProcessor::ProcessUserInput( string sInput )
{
	//if the user has not given any username yet
	if(this->e_CurrentState == LOGIN_USERNAME_PENDING)
	{
		//create the login message
		this->o_MsgParser->CreateLoginMessage(&sInput);
		this->o_NetworkSocketOp->WriteToSocket(sInput.c_str(),sInput.length());
		this->e_CurrentState=LOGIN_USERNAME_SENT;
	}

}

MessageProcessor::MessageProcessor( MessageParser * oMsgParser, SocketOperator * oNetworkSocketOp, SocketOperator * oTerminalSocketOp )
{
	this->o_MsgParser=oMsgParser;
	this->o_NetworkSocketOp=oNetworkSocketOp;
	this->o_TerminalSocketOp=oTerminalSocketOp;

	//set the initial client state
	this->e_CurrentState=LOGIN_USERNAME_PENDING;
}
