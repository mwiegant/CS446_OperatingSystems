# ./simOX os_files/config_1.conf

CC = g++
DEBUG = -g
CFLAGS = -Wall -c
LFLAGS = -Wall

simOX : src/main.cpp Simulation.o
	$(CC) $(LFLAGS) src/main.cpp Simulation.o -o simOX

Simulation.o : Simulation.o src/Simulation.cpp
	$(CC) $(CFLAGS) src/Simulation.cpp


clean:
	\rm *.o simOX

