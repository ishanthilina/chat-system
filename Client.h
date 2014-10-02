#ifndef _CLIENT_HEADER_
#define _CLIENT_HEADER_

#include <string>
#include <cstdio>	//defines sprintf
#include <netinet/in.h>
#include <arpa/inet.h>

#include <iostream>

using namespace std;

class Client
{
public:
	Client(string s_UserName, int i_Socket,sockaddr_in o_address);
	string GetUserName();
	string GetLogName();
	int GetSocket();
	sockaddr_in GetAddressStruct();
protected:
private:
	string s_UserName;
	int i_Socket;
	string s_LogName;
	sockaddr_in o_address;
};

#endif	//_CLIENT_HEADER_
