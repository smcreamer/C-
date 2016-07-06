main: project1driver.o list.o
	g++ project1driver.o list.o data.o -o main
	
list.o: list.cpp linkedlist.h
	g++ -c linkedlist.cpp
	
data.o: data.cpp data.h
	g++ -c data.cpp
	
clean: 
	rm *.o main