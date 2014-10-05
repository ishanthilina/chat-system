CXXFLAGS =	-O2 -g -Wall -fmessage-length=0

OBJS =		client.o SocketOperator.o ChatClient.o EventListener.o EventHandler.o

LIBS =

TARGET =	client

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
