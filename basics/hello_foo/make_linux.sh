g++ foo.cpp -std=c++11 -Wall -o foo.o -c
g++ main.cpp -std=c++11 -Wall -o main.o -c
g++ -std=c++11 -Wall -o hello main.o foo.o

