#include "MessageFactory.h"


Message MessageFactory::createMessage( int i_sender, string s_Message )
{

}

MessageType MessageFactory::getMessageType( string s_Message )
{
	string sType = s_Message.substr(0,s_Message.find_first_of(";"));


}

MessageFactory::MessageFactory()
{
	 this->c_MessageSeperator=';';
}
