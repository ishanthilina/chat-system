#include "Client.h"


Client::Client( string s_UserName, int i_Socket, sockaddr_in o_address)
{

	//remove the new line character from the string
	s_UserName.erase(s_UserName.find_last_not_of(" \n\r\t")+1);

	this->s_UserName = s_UserName;
	this->i_Socket = i_Socket;
	this->o_address = o_address;


	this->s_LogName = s_UserName+"-"+string(inet_ntoa(o_address.sin_addr));
			//+"-"+string(s_Port);
}

std::string Client::GetUserName()
{
	return s_UserName;
}

std::string Client::GetLogName()
{
	return s_LogName;
}

int Client::GetSocket()
{
	return i_Socket;
}

sockaddr_in Client::GetAddressStruct()
{
	return o_address;
}
