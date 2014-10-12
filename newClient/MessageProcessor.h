#ifndef _MESSAGE_PROCESSOR_HEADER_
#define _MESSAGE_PROCESSOR_HEADER_

#include <string>


#include "MessageParser.h"
#include "SocketOperator.h"
#include "ScreenWriter.h"
#include "Utils.h"

using namespace std;

enum ClientState
		{
			LOGIN_USERNAME_PENDING=0,
			LOGIN_USERNAME_SENT=1,
			LOGGED_IN=2
		};

class MessageProcessor
{
public:

	MessageProcessor(MessageParser * oMsgParser, SocketOperator * oNetworkSocketOp, SocketOperator * oTerminalSocketOp,ScreenWriter * oScreenWriter);
	void ProcessUserInput(string sInput);
	void ProcessServerInput(string sInput);
	void SetClientState(enum ClientState eClientState);



protected:
private:
	ClientState e_CurrentState;
	MessageParser * o_MsgParser;
	SocketOperator * o_NetworkSocketOp;
	SocketOperator * o_TerminalSocketOp;
	ScreenWriter * o_ScreenWriter;

	void TrimWhitespace(string& str);
};

#endif	//_MESSAGE_PROCESSOR_HEADER_
