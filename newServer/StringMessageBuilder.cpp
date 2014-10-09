#include "StringMessageBuilder.h"

//TODO- methods can be refactored reducing the code duplications

// |;|7+4+2+5|LIN;ishan|;|
int StringMessageBuilder::CreateNotificationMessage( string * sMessageContent )
{
	//get the protocol string
	string sProtocol(GetTextForEnum(NOTIFICATION));

	//get total message length
	int iMsgLength = (*sMessageContent).length()+GetMessageHeader().length()+GetMessageFooter().length()+sProtocol.length()+8;
	char zBuf[4];
	memset(zBuf, 0, 4);
	sprintf(zBuf, "%d", iMsgLength);
	string sMsgLength=string(zBuf);
	while (sMsgLength.length()<7)	//set the length of message header items length constant
	{
		sMsgLength.insert(0,"0");
	}


	string sNotifMsg=GetMessageHeader();
	sNotifMsg.append(sMsgLength);
	sNotifMsg.append("|");
	sNotifMsg.append(sProtocol);
	sNotifMsg.append(*sMessageContent);
	sNotifMsg.append(GetMessageFooter());
	(*sMessageContent)=sNotifMsg;
	return 0;
}

int StringMessageBuilder::CreateChatMessage(string* sMessageContent)
{
	//get the protocol string
		string sProtocol(GetTextForEnum(DIRECT));

		//get total message length
		int iMsgLength = (*sMessageContent).length()+GetMessageHeader().length()+GetMessageFooter().length()+sProtocol.length()+8;
		
		//cout<<"1-"<<iMsgLength<<endl;
		char zBuf[4];
		memset(zBuf, 0, 4);
		sprintf(zBuf, "%d", iMsgLength);

		string sMsgLength=string(zBuf);
		while (sMsgLength.length()<7)	//set the length of message header items length constant
		{
			sMsgLength.insert(0,"0");
		}

		//cout<<"2-"<<sMsgLength<<endl;

		string sNotifMsg=GetMessageHeader();
		sNotifMsg.append(sMsgLength);
		//sNotifMsg.append(string(zBuf));
		sNotifMsg.append("|");
		sNotifMsg.append(sProtocol);
		sNotifMsg.append(*sMessageContent);
		sNotifMsg.append(GetMessageFooter());
		(*sMessageContent)=sNotifMsg;
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
	int iMsgLength = (sMessageContent).length()+GetMessageHeader().length()+GetMessageFooter().length()+sProtocol.length()+8;
	char zBuf[4];
	memset(zBuf, 0, 4);
	sprintf(zBuf, "%d", iMsgLength);

	string sMsgLength=string(zBuf);
	while (sMsgLength.length()<7)	//set the length of message header items length constant
	{
		sMsgLength.insert(0,"0");
	}


	string sMsg=GetMessageHeader();
	sMsg.append(sMsgLength);
	sMsg.append("|");
	sMsg.append(sProtocol);
	sMsg.append(sMessageContent);
	sMsg.append(GetMessageFooter());

	return sMsg;
}
