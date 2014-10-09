#include "MessageProcessor.h"

void MessageProcessor::ProcessUserInput( string sInput )
{
	//cout<<"UserInput"<<endl;
	//if the user has not given any username yet
	if(this->e_CurrentState == LOGIN_USERNAME_PENDING)
	{
		//create the login message
		this->o_MsgParser->CreateLoginMessage(&sInput);
		int result=this->o_NetworkSocketOp->WriteToSocket(sInput.c_str(),sInput.length());
		if(result)
		{
			cout<<"[INFO] Bad Input."<<endl;
			return;
		}
		this->e_CurrentState=LOGIN_USERNAME_SENT;
	}
	//if waiting for authentication after sending username
	else if(this->e_CurrentState == LOGIN_USERNAME_SENT)
	{
		//		if(sInput.compare("Login Success!")==0)
		//		{
		//			cout<<"Succesfully Logged in!"<<endl;
		//			this->e_CurrentState=LOGGED_IN;
		//		}
		//		else
		//		{
		//			cout<<"Login Failed!"<<endl;
		//			this->e_CurrentState=LOGIN_USERNAME_PENDING;
		//			std::cout<<"Please Enter UserName: "<<std::endl;
		//		}
	}
	//if logged in
	else if(this->e_CurrentState == LOGGED_IN)
	{
		//send as a message
		int result=this->o_MsgParser->CreateChatMessage(&sInput);

		if(result)
		{
			cout<<"[INFO] Bad Input."<<endl;
			return;
		}
		this->o_NetworkSocketOp->WriteToSocket(sInput.c_str(),sInput.length());

	}

}

void MessageProcessor::ProcessServerInput( string sInput )
{
	//cout<<this->e_CurrentState<<endl;
	cout<<sInput<<endl;

	//if the user has not given any username yet
	if(this->e_CurrentState == LOGIN_USERNAME_PENDING)
	{
		//create the login message
		//this->o_MsgParser->CreateLoginMessage(&sInput);
		//this->o_NetworkSocketOp->WriteToSocket(sInput.c_str(),sInput.length());
		//this->e_CurrentState=LOGIN_USERNAME_SENT;
	}
	//if waiting for authentication after sending username
	else if(this->e_CurrentState == LOGIN_USERNAME_SENT)
	{
		//cout<<o_MsgParser->GetMessageType(sInput)<<endl;
		//if this is a reply to the authentication request
		if(o_MsgParser->GetMessageType(sInput) == AUTHENTICATION)
		{
			if(o_MsgParser->GetMessageContent(sInput).compare("success")==0)
			{
				cout<<"Successfully Logged in!"<<endl;
				this->e_CurrentState=LOGGED_IN;
			}
			else
			{
				cout<<"Login Failed!"<<endl;
				this->e_CurrentState=LOGIN_USERNAME_PENDING;
				std::cout<<"Please Enter UserName: "<<std::endl;
			}
		}

	}
	//if logged in
	else if(this->e_CurrentState == LOGGED_IN)
	{
		cout<<"[CHAT] "<<o_MsgParser->GetMessageContent(sInput)<<endl;
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
