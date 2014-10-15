#ifndef _CLIENT_HEADER_
#define _CLIENT_HEADER_

#include <algorithm>
#include <string>
#include <cstdio>	//defines sprintf
#include <netinet/in.h>
#include <arpa/inet.h>
//#include "Utils.h"

#include <iostream>

using namespace std;

class User
{
public:
	User(string s_UserName, Client* pClient);
	string GetUserName();
	string GetLogName();
	int GetClient();
protected:
private:
	string s_UserName;
	string s_LogName;
	Client* p_Client;
};

#endif	//_CLIENT_HEADER_
