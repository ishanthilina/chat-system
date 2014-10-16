#include "User.h"


User::User(string s_UserName, Client* pClient)
{

	//remove the new line character from the string
	s_UserName.erase(s_UserName.find_last_not_of(" \n\r\t")+1);

	this->s_UserName = s_UserName;
	this->p_Client = pClient;


	this->s_LogName = s_UserName;
		//+"-"+string(inet_ntoa(o_address.sin_addr));
			//+"-"+string(s_Port);
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

