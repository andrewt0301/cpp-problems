all: main.o foo.o
	g++ -std=c++11 -Wall -o hello main.o foo.o

main.o: main.cpp
	g++ main.cpp -std=c++11 -Wall -o main.o -c

foo.o: foo.cpp
	g++ foo.cpp -std=c++11 -Wall -o foo.o -c


