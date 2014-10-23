#include "MessageParser.h"

static const char * EnumStrings[] = { "LIN;", "PTP;", "LOU;", "NTF;", "AUT;" };

const char * GetTextForEnum( int iEnumVal )
{
	return EnumStrings[iEnumVal];
}

const MessageType GetEnumFromString(string sEnumStr)
{
	MessageType oReturnType;
	bool bReturnTypeWasSet=false;
	for (int i=0; i<5;i++){
		if (sEnumStr.compare(EnumStrings[i])==0)
		{
			oReturnType=static_cast<MessageType>(i);
			bReturnTypeWasSet=true;
			break;
		}
	}
	if (!bReturnTypeWasSet)
	{
		oReturnType=ERROR;
	}

	return oReturnType;
}

std::string GetMessageHeader()
{
	return string("|;|");
}

std::string GetMessageFooter()
{
	return string("|;|");
}

int GetTotalHeaderLength()
{
	return 11;
}

int GetTotalFooterLength()
{
	return 3;
}

int MessageParser::CreateLoginMessage( string* spMessageContent )
{
	//validate the string first
	std::size_t iFound = (*spMessageContent).find(";");
	if (iFound!=std::string::npos)
	{
		return 1;
	}


	//get the protocol string
	string sProtocol(GetTextForEnum(LOGIN));

	//get total message length
	int iMsgLength = (*spMessageContent).length()+GetMessageHeader().length()+GetMessageFooter().length()+sProtocol.length()+8;
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
	sNotifMsg.append(*spMessageContent);
	sNotifMsg.append(GetMessageFooter());
	(*spMessageContent)=sNotifMsg;
	return 0;

}

int MessageParser::CreateChatMessage( string* spMessageContent )
{
	//validate the string first
	std::size_t iFound = (*spMessageContent).find(";");
	if (iFound==std::string::npos || iFound ==0)
	{
		return 1;
	}

	//get the protocol string
	string sProtocol(GetTextForEnum(DIRECT));

	//get total message length
	int iMsgLength = (*spMessageContent).length()+GetMessageHeader().length()+GetMessageFooter().length()+sProtocol.length()+8; //+ the length of the number

	char zBuf[64];
	memset(zBuf, 0, 64);
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
	sNotifMsg.append(*spMessageContent);
	sNotifMsg.append(GetMessageFooter());
	(*spMessageContent)=sNotifMsg;
	return 0;

}

MessageType MessageParser::GetMessageType(string sMessageContent) 
{
	return GetEnumFromString(sMessageContent.substr(0,4));
}

string MessageParser::GetMessageContent(string sMessageContent) 
{
	return sMessageContent.substr(4);
}
