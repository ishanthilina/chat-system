all:
	if [ -a *.gch ]; then rm *.gch; fi;		
	if [ -a chatServer ]; then rm chatServer; fi;
	g++ *.h *.cpp -o chatServer