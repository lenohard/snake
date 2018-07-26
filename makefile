CC=g++
CFLAGS = -g -lncurses
snake: main.o Wall.o Snake.o Food.o Stat.o
	g++ -o snake main.o Wall.o Snake.o Food.o Stat.o $(CFLAGS)

main.o: main.cpp Wall.hpp main.hpp Food.hpp Snake.hpp Stat.hpp
	g++ -c  main.cpp Wall.hpp Food.hpp Snake.hpp Stat.hpp $(CFLAGS)

Wall.o: Wall.hpp Wall.cpp 
	g++ -c Wall.hpp Wall.cpp $(CFLAGS)

Snake.o: Snake.hpp Snake.cpp main.hpp 
	g++ -c $(CFLAGS)  Snake.cpp Snake.hpp main.hpp

Food.o: Food.hpp Food.cpp main.hpp 
	g++ -c $(CFLAGS) Food.hpp Food.cpp main.hpp 

Stat.o: Stat.hpp Stat.cpp main.hpp Snake.hpp
	g++ -c $(CFLAGS) Stat.hpp Stat.cpp main.hpp Snake.hpp
all: snake
