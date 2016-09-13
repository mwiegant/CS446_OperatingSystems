# ./simOX os_files/config_1.conf

CC = g++
DEBUG = -g
CFLAGS = -Wall -c
LFLAGS = -Wall

simOX : src/main.cpp Processor.o Simulation.o
	$(CC) $(LFLAGS) src/main.cpp Processor.o Simulation.o -o simOX

Processor.o : Processor.o src/Processor.cpp
	$(CC) $(CFLAGS) src/Processor.cpp

Simulation.o : Simulation.o src/Simulation.cpp
	$(CC) $(CFLAGS) src/Simulation.cpp


clean:
	\rm *.o simOX

