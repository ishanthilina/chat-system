
Client::Client( string s_UserName, int i_Socket, sockaddr_in o_address)
{
	this->s_UserName = s_UserName;
	this->i_Socket = i_Socket;
	this->o_address = o_address;

	this->s_LogName = s_UserName+"-"+inet_ntoa(address.sin_addr)+"-"+ntohs(address.sin_port);
}

std::string Client::GetUserName()
{
	return s_UserName;
}

std::string Client::GetLogNanme()
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
