#ifndef _USER_HEADER_
#define _USER_HEADER_

#include <algorithm>
#include <string>
#include <cstdio>	//defines sprintf
#include <netinet/in.h>
#include <arpa/inet.h>
#include "Client.h"
#include "Message.h"

#include <iostream>

using namespace std;

class User
{
public:
	User(string s_UserName, Client* pClient);
	string GetUserName();
	string GetLogName();
	Client* GetClient();
	int SendMessage(string sMsg);
protected:
private:
	string s_UserName;
	string s_LogName;
	Client* p_Client;
};

#endif	//_USER_HEADER_
