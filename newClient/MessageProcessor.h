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

	MessageProcessor(MessageParser * pMsgParser, SocketOperator * pNetworkSocketOp, SocketOperator * pTerminalSocketOp,ScreenWriter * pScreenWriter);
	void ProcessUserInput(string sInput);
	void ProcessServerInput(string sInput);
	void SetClientState(enum ClientState eClientState);



protected:
private:
	ClientState e_CurrentState;
	MessageParser * p_MsgParser;
	SocketOperator * p_NetworkSocketOp;
	SocketOperator * p_TerminalSocketOp;
	ScreenWriter * p_ScreenWriter;

	void TrimWhitespace(string& sString);
};

#endif	//_MESSAGE_PROCESSOR_HEADER_
