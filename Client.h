#include <string>
#include <netinet/in.h>
#include <arpa/inet.h>

using namespace std;

class Client
{
public:
	Client(string s_UserName, int i_Socket,sockaddr_in o_address);
	string GetUserName();
	string GetLogNanme();
	int GetSocket();
	sockaddr_in GetAddressStruct();
protected:
private:
	string s_UserName;
	int i_Socket;
	string s_LogName;
	sockaddr_in o_address;
};