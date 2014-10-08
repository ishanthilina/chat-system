#include "MessageParser.h"

static const char * EnumStrings[] = { "LIN;", "PTP;", "LOU;", "NTF;", "AUT;" };

const char * GetTextForEnum( int i_EnumVal )
{
	return EnumStrings[i_EnumVal];
}

const MessageType GetEnumFromString(string s_EnumStr){
	MessageType oReturnType;
	bool bReturnTypeWasSet=false;
	for (int i=0; i<5;i++){
		if (s_EnumStr.compare(EnumStrings[i])==0)
		{
			oReturnType=static_cast<MessageType>(i);
			bReturnTypeWasSet=true;
			//cout<<i;
			break;
		}
		//cout<<"No : "<<i<<":"<<s_EnumStr;
	}
	if (!bReturnTypeWasSet)
	{
		//cout<<"ErroR";
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

int MessageParser::CreateLoginMessage( string* sMessageContent )
{
	//validate the string first
	std::size_t found = (*sMessageContent).find(";");
	if (found!=std::string::npos)
	{
		return 1;
	}


	//get the protocol string
	string sProtocol(GetTextForEnum(LOGIN));

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

int MessageParser::CreateChatMessage( string* sMessageContent )
{
	//validate the string first
	std::size_t found = (*sMessageContent).find(";");
	if (found==std::string::npos)
	{
		return 1;
	}


	//get the protocol string
	string sProtocol(GetTextForEnum(DIRECT));

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

MessageType MessageParser::GetMessageType(string sMessageContent) {
	return GetEnumFromString(sMessageContent.substr(0,4));
}

string MessageParser::GetMessageContent(string sMessageContent) {
	return sMessageContent.substr(4,sMessageContent.length()-(4+3));
}
