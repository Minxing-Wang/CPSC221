all : dates lists 
	echo "all compiled"

dates : dates.cc CDate.o Unit.o 
	g++ -Wall dates.cc CDate.o Unit.o  -o dates

CDate.o : CDate.cc CDate.h 
	g++ -Wall -c CDate.cc -o CDate.o 

lists : lists.cc linked_list.cc Unit.o
	g++ -Wall lists.cc Unit.o -o lists 

Unit.o : Unit.cc Unit.h  
	g++ -Wall -c Unit.cc -o Unit.o 

clean :
	rm -f CDate.o 
	rm -f dates 
	rm -f Unit.o 
	rm -f lists
 
