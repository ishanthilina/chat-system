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
		this->o_MsgParser->CreateLoginMessage(&sInput);
		int result=this->o_NetworkSocketOp->WriteToSocket(sInput.c_str(),sInput.length());
		if(result)
		{
			o_ScreenWriter->WriteNotificationMessage("Bad Input.");
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

		//cout<<endl<<endl<<sInput<<endl<<endl;
		//send as a message
		int result=this->o_MsgParser->CreateChatMessage(&sInput);

		//cout<<endl<<endl<<sInput<<endl<<endl;

		if(result)
		{
			o_ScreenWriter->WriteNotificationMessage("Bad Input.");
			return;
		}
		this->o_NetworkSocketOp->WriteToSocket(sInput.c_str(),sInput.length());

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
		if(o_MsgParser->GetMessageType(sInput) == AUTHENTICATION)
		{
			if(o_MsgParser->GetMessageContent(sInput).compare("success")==0)
			{
				o_ScreenWriter->WriteNotificationMessage("Successfully Logged in!");
				this->e_CurrentState=LOGGED_IN;
			}
			else
			{
				o_ScreenWriter->WriteNotificationMessage("Login Failed!");
				this->e_CurrentState=LOGIN_USERNAME_PENDING;
				o_ScreenWriter->WriteNotificationMessage("Please Re-Enter UserName: ");
			}
		}

	}
	//if logged in
	else if(this->e_CurrentState == LOGGED_IN)
	{
		LogDebug("MessageProcessor.cpp - Current State : %s","LOGGED_IN");

		if(o_MsgParser->GetMessageType(sInput) == NOTIFICATION)
		{
			o_ScreenWriter->WriteNotificationMessage(o_MsgParser->GetMessageContent(sInput));
		}
		else
		{
			o_ScreenWriter->WriteChatMessage(o_MsgParser->GetMessageContent(sInput));
		}


	}

}

MessageProcessor::MessageProcessor( MessageParser * oMsgParser, SocketOperator * oNetworkSocketOp, SocketOperator * oTerminalSocketOp, ScreenWriter * oScreenWriter )
{
	this->o_MsgParser=oMsgParser;
	this->o_NetworkSocketOp=oNetworkSocketOp;
	this->o_TerminalSocketOp=oTerminalSocketOp;
	this->o_ScreenWriter=oScreenWriter;

	//set the initial client state
	this->e_CurrentState=LOGIN_USERNAME_PENDING;
}

void MessageProcessor::SetClientState(enum ClientState eClientState)
{
	this->e_CurrentState = eClientState;
}


void MessageProcessor::TrimWhitespace(string& input) {
	if(input.find_first_of(";")!=string::npos)
	{
		string::size_type pos = input.find_last_not_of(' ');
		if(pos != string::npos) {
			input.erase(pos + 1);
			pos = input.find_first_not_of(' ');
			if(pos != string::npos) input.erase(0, pos);
		}
		else input.erase(input.begin(), input.end());

		string str=input.substr(input.find_first_of(";")+1);
		pos = str.find_last_not_of(' ');
		if(pos != string::npos) {
			str.erase(pos + 1);
			pos = str.find_first_not_of(' ');
			if(pos != string::npos) str.erase(0, pos);
		}
		else str.erase(str.begin(), str.end());
		input.erase(input.find_first_of(";")+1);
		input.replace(input.find_first_of(";")+1,str.length(),str);
	}

}
