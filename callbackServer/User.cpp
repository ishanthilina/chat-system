#include "User.h"


User::User(string sUserName, Client* pClient)
{

	//remove the new line character from the string
	sUserName.erase(sUserName.find_last_not_of(" \n\r\t")+1);

	s_UserName = sUserName;
	p_Client = pClient;


	s_LogName = sUserName;

}

std::string User::GetUserName()
{
	return s_UserName;
}

std::string User::GetLogName()
{
	return s_LogName;
}

Client* User::GetClient()
{
	return p_Client;
}

int User::SendMessage(string sMsg)
{
	Message* pChatMsg = new Message(sMsg);
	return p_Client->SendMessage(pChatMsg);
	delete pChatMsg;
}

