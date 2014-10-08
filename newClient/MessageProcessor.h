#ifndef _MESSAGE_PROCESSOR_HEADER_
#define _MESSAGE_PROCESSOR_HEADER_

#include <string>


#include "MessageParser.h"
#include "SocketOperator.h"

using namespace std;

class MessageProcessor
{
public:
	MessageProcessor(MessageParser * oMsgParser, SocketOperator * oNetworkSocketOp, SocketOperator * oTerminalSocketOp);
	void ProcessUserInput(string sInput);
	void ProcessServerInput(string sInput);

	enum ClientState
	{
		LOGIN_USERNAME_PENDING=0,
		LOGIN_USERNAME_SENT=1,
		LOGGED_IN=2
	};

protected:
private:
	ClientState e_CurrentState;
	MessageParser * o_MsgParser;
	SocketOperator * o_NetworkSocketOp;
	SocketOperator * o_TerminalSocketOp;
};

#endif	//_MESSAGE_PROCESSOR_HEADER_
