#ifndef _SCREEN_WRITER_HEADER_
#define _SCREEN_WRITER_HEADER_

#include <string>
#include <iostream>

using namespace std;

class ScreenWriter
{
public:
	ScreenWriter();
	void WriteChatMessage(string sMessage);
	void WriteNotificationMessage(string sMessage);
protected:
private:
};

#endif	//_SCREEN_WRITER_HEADER_
