CC=g++
CFLAGS = -g -Wall -lncurses
snake: main.o Wall.o Snake.o Food.o Stat.o
	g++ -o snake main.o Wall.o Snake.o Food.o Stat.o $(CFLAGS)

main.o: main.cpp Wall.hpp main.hpp Food.hpp Snake.hpp Stat.hpp
	g++ -c  main.cpp $(CFLAGS)

Wall.o: Wall.hpp Wall.cpp 
	g++ -c Wall.cpp $(CFLAGS)

Snake.o: Snake.hpp Snake.cpp main.hpp 
	g++ -c $(CFLAGS)  Snake.cpp 

Food.o: Food.hpp Food.cpp main.hpp 
	g++ -c $(CFLAGS) Food.cpp 

Stat.o: Stat.hpp Stat.cpp main.hpp Snake.hpp
	g++ -c $(CFLAGS) Stat.cpp 

clean:
	-rm main.o Stat.o Food.o Wall.o Snake.o snake
all: snake
