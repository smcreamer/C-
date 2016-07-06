main: test.o hashtable.o data.o
	g++ test.o hashtable.o data.o -o main

hashtable.o: hashtable.cpp hashtable.h data.cpp
	g++ -c hashtable.cpp data.cpp

data.o: data.cpp data.h
	g++ -c data.cpp

clean:
	rm -f *.o main
