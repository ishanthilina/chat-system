#include "User.h"


User::User(string sUserName, Client* pClient)
{

	//remove the new line character from the string
	sUserName.erase(sUserName.find_last_not_of(" \n\r\t")+1);

	this->s_UserName = sUserName;
	this->p_Client = pClient;


	this->s_LogName = sUserName;

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
	return this->p_Client;
}

int User::SendMessage(string sMsg)
{
	return this->p_Client->SendMessage(sMsg);
}

