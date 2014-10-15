CXXFLAGS =	-O2 -g -Wall -fmessage-length=0

OBJS =	Client.o EventManager.o Server.o ServerSideCallBack.o User.o UserRegistry.o Utils.o	Message.o MessageBuffer.o DeliveryController.o

LIBS =

TARGET =	callBackServer

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
