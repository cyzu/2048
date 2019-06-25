# Makefile 2048 game cyzu - 2019 March 5

SHELL	= /bin/bash
CC 	= g++
CFLAGS 	= -std=c++11 -Wall -pedantic
NCURSES = -lncurses

CFILES 	= src/main.cpp src/game.cpp obj/Matrix.cpp
EXEC 	= bin/game_2048
OBJECTS	= bin/main.o bin/game.o bin/Matrix.o


all :: $(EXEC)

$(EXEC): $(OBJECTS)
	$(CC) -g -o $(EXEC) $(OBJECTS) $(CFLAGS) $(NCURSES)

bin/main.o: src/main.cpp
	$(CC) -g -c -o $@ $^ $(CFLAGS)

bin/game.o: src/game.cpp src/game.h
	$(CC) -g -c -o $@ src/game.cpp $(CFLAGS)

bin/Matrix.o: obj/Matrix.cpp obj/Matrix.h
	$(CC) -g -c -o $@ obj/Matrix.cpp $(FLAGS)

clean ::
	rm -f bin/*.o $(EXEC)
#	echo 0 > doc/highScore

#--------------------------------------------------------------------
#bin/game.o: src/game.cpp src/game.h src/ObjectField.h
#    $(GCC) -g -c -o bin/game.o src/game.cpp $(CFLAGS)
#
#bin/ObjectField.o: src/ObjectField.cpp src/ObjectField.h
#    $(GCC) -g -c -o bin/ObjectField.o src/ObjectField.cpp $(CFLAGS)
#--------------------------------------------------------------------
