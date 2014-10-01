all:
	if [ -a *.gch ]; then rm *.gch; fi;		
	g++ Message.h Message.cpp MessageFactory.h MessageFactory.cpp -o chatServer