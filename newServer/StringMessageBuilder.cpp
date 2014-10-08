#include "StringMessageBuilder.h"

// |;|7+4+2+5|LIN;ishan|;|
int StringMessageBuilder::CreateNotificationMessage( string * sMessageContent )
{
	//get the protocol string
	string sProtocol(GetTextForEnum(NOTIFICATION));

	//get total message length
	int iMsgLength = (*sMessageContent).length()+GetMessageHeader().length()+GetMessageFooter().length()+sProtocol.length()+3;
	char zBuf[2];
	sprintf(zBuf, "%d", iMsgLength);

	string sNotifMsg=GetMessageHeader();
	sNotifMsg.append(string(zBuf));
	sNotifMsg.append(sProtocol);
	sNotifMsg.append(*sMessageContent);
	sNotifMsg.append(GetMessageFooter());
	(*sMessageContent)=sNotifMsg;
	return 0;
}
