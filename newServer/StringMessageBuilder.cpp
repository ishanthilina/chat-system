#include "StringMessageBuilder.h"

// |;|7+4+2+5|LIN;ishan|;|
int StringMessageBuilder::CreateNotificationMessage( string * sMessageContent )
{
	int iMsgLength = (*sMessageContent).length()+GetMessageHeader().length()+GetMessageFooter().length()+3+3;
	string sNotifMsg="LIN;";
	sNotifMsg.append(*sMessageContent);
	(*sMessageContent)=sNotifMsg;
	return 0;
}
