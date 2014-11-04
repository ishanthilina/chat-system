CXXFLAGS =	-O2 -g -Wall -fmessage-length=0

OBJS =	ChatMessage.o Client.o DeliveryController.o EventManager.o Logger.o Message.o MessageFactory.o MyServer.o Server.o ServerSideCallBack.o ServersClientIterator.o User.o UserRegistry.o Utils.o

LIBS =

TARGET =	callBackServer

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
