#include "MessageParser.h"

int MessageParser::CreateLoginMessage( string* sMessageContent )
{
	//validate the string first
	std::size_t found = (*sMessageContent).find(";");
	if (found!=std::string::npos)
	{
		return 1;
	}

	string sLoginMsg="LIN;";
	sLoginMsg.append(*sMessageContent);
	(*sMessageContent)=sLoginMsg;
	return 0;

}
