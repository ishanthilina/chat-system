CXXFLAGS =	-O2 -g -Wall -fmessage-length=0

OBJS =		Client.o ClientRegistry.o Logger.o Message.o MessageBuffer.o MessageFactory.o Server.o SocketOperator.o StringMessageBuilder.o 

LIBS =

TARGET =	server

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
