CXXFLAGS =	-O2 -g -Wall -fmessage-length=0

OBJS =	Client.o DeliveryController.o EventManager.o Logger.o Message.o MessageBuffer.o MessageFactory.o MyServer.o Server.o ServerSideCallBack.o User.o UserRegistry.o Utils.o

LIBS =

TARGET =	callBackServer

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
