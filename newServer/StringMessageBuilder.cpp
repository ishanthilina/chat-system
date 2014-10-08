#include "StringMessageBuilder.h"

//TODO- methods can be refactored reducing the code duplications

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
	sNotifMsg.append("|");
	sNotifMsg.append(sProtocol);
	sNotifMsg.append(*sMessageContent);
	sNotifMsg.append(GetMessageFooter());
	(*sMessageContent)=sNotifMsg;
	return 0;
}

int StringMessageBuilder::CreateChatMessage(string* sMessageContent)
{
	return 0;
}

string StringMessageBuilder::CreateAuthStatusMessage(bool bAuthStatus) {

	//get the protocol string
	string sProtocol(GetTextForEnum(AUTHENTICATION));

	string sMessageContent;
	if(bAuthStatus){
		(sMessageContent)="success";
	}
	else{
		(sMessageContent)="failure";
	}

	//get total message length
	int iMsgLength = (sMessageContent).length()+GetMessageHeader().length()+GetMessageFooter().length()+sProtocol.length()+3;
	char zBuf[2];
	sprintf(zBuf, "%d", iMsgLength);

	string sMsg=GetMessageHeader();
	sMsg.append(string(zBuf));
	sMsg.append("|");
	sMsg.append(sProtocol);
	sMsg.append(sMessageContent);
	sMsg.append(GetMessageFooter());

	return sMsg;
}
