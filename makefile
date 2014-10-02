all:
	if [ -a *.gch ]; then rm *.gch; fi;		
	g++ *.h *.cpp -o chatServer