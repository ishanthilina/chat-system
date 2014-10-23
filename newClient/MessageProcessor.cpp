#include "MessageProcessor.h"

void MessageProcessor::ProcessUserInput( string sInput )
{

	//trim whitespace
	TrimWhitespace(sInput);

	LogDebug("MessageProcessor.cpp - Processing User Input");
	//if the user has not given any username yet
	if(this->e_CurrentState == LOGIN_USERNAME_PENDING)
	{
		LogDebug("MessageProcessor.cpp - Current State : %s","LOGIN_USERNAME_PENDING");
		//create the login message
		int result=this->p_MsgParser->CreateLoginMessage(&sInput);
		if(result)
		{
			p_ScreenWriter->WriteNotificationMessage("Bad Input.");
			this->e_CurrentState=LOGIN_USERNAME_PENDING;
			p_ScreenWriter->WriteNotificationMessage("Please Re-Enter UserName: ");
			return;
		}
		result=this->p_NetworkSocketOp->WriteToSocket(sInput.c_str(),sInput.length());
		if(result)
		{
			p_ScreenWriter->WriteNotificationMessage("Bad Input.");
			return;
		}
		this->e_CurrentState=LOGIN_USERNAME_SENT;
	}
	//if waiting for authentication after sending username
	else if(this->e_CurrentState == LOGIN_USERNAME_SENT)
	{
		LogDebug("MessageProcessor.cpp - Current State : %s","LOGIN_USERNAME_SENT");
	}
	//if logged in
	else if(this->e_CurrentState == LOGGED_IN)
	{
		LogDebug("MessageProcessor.cpp - Current State : %s","LOGGED_IN");

		//send as a message
		int result=this->p_MsgParser->CreateChatMessage(&sInput);

		if(result)
		{
			p_ScreenWriter->WriteNotificationMessage("Bad Input.");
			return;
		}
		this->p_NetworkSocketOp->WriteToSocket(sInput.c_str(),sInput.length());

	}

}

void MessageProcessor::ProcessServerInput( string sInput )
{
	LogDebug("MessageProcessor.cpp - Processing Server Input");

	//if the user has not given any username yet
	if(this->e_CurrentState == LOGIN_USERNAME_PENDING)
	{
		LogDebug("MessageProcessor.cpp - Current State : %s","LOGIN_USERNAME_PENDING");
	}
	//if waiting for authentication after sending username
	else if(this->e_CurrentState == LOGIN_USERNAME_SENT)
	{
		LogDebug("MessageProcessor.cpp - Current State : %s","LOGIN_USERNAME_SENT");

		//if this is a reply to the authentication request
		if(p_MsgParser->GetMessageType(sInput) == AUTHENTICATION)
		{
			if(p_MsgParser->GetMessageContent(sInput).compare("success")==0)
			{
				p_ScreenWriter->WriteNotificationMessage("Successfully Logged in!");
				this->e_CurrentState=LOGGED_IN;
			}
			else
			{
				p_ScreenWriter->WriteNotificationMessage("Login Failed!");
				this->e_CurrentState=LOGIN_USERNAME_PENDING;
				p_ScreenWriter->WriteNotificationMessage("Please Re-Enter UserName: ");
			}
		}

	}
	//if logged in
	else if(this->e_CurrentState == LOGGED_IN)
	{
		LogDebug("MessageProcessor.cpp - Current State : %s","LOGGED_IN");

		if(p_MsgParser->GetMessageType(sInput) == NOTIFICATION)
		{
			p_ScreenWriter->WriteNotificationMessage(p_MsgParser->GetMessageContent(sInput));
		}
		else
		{
			p_ScreenWriter->WriteChatMessage(p_MsgParser->GetMessageContent(sInput));
		}


	}

}

MessageProcessor::MessageProcessor( MessageParser * oMsgParser, SocketOperator * oNetworkSocketOp, SocketOperator * oTerminalSocketOp, ScreenWriter * oScreenWriter )
{
	this->p_MsgParser=oMsgParser;
	this->p_NetworkSocketOp=oNetworkSocketOp;
	this->p_TerminalSocketOp=oTerminalSocketOp;
	this->p_ScreenWriter=oScreenWriter;

	//set the initial client state
	this->e_CurrentState=LOGIN_USERNAME_PENDING;
}

void MessageProcessor::SetClientState(enum ClientState eClientState)
{
	this->e_CurrentState = eClientState;
}


void MessageProcessor::TrimWhitespace(string& sInput) 
{
	if(sInput.find_first_of(";")!=string::npos)
	{
		string::size_type iPos = sInput.find_last_not_of(' ');
		if(iPos != string::npos) {
			sInput.erase(iPos + 1);
			iPos = sInput.find_first_not_of(' ');
			if(iPos != string::npos) sInput.erase(0, iPos);
		}
		else sInput.erase(sInput.begin(), sInput.end());

		string str=sInput.substr(sInput.find_first_of(";")+1);
		iPos = str.find_last_not_of(' ');
		if(iPos != string::npos) {
			str.erase(iPos + 1);
			iPos = str.find_first_not_of(' ');
			if(iPos != string::npos) str.erase(0, iPos);
		}
		else str.erase(str.begin(), str.end());
		sInput.erase(sInput.find_first_of(";")+1);
		sInput.replace(sInput.find_first_of(";")+1,str.length(),str);
	}

}
