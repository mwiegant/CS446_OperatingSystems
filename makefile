# Max Wiegant
# 9 - 10 - 16
# Make Peace, not Bugs

CC = g++
DEBUG = -g
CFLAGS = -Wall -c
LFLAGS = -Wall

SimO1 : src/main.cpp Processor.o Logger.o Metadata.o Simulation.o
	$(CC) $(LFLAGS) src/main.cpp Processor.o Logger.o Metadata.o Simulation.o -o Sim01

Processor.o : Processor.o src/Processor.cpp
	$(CC) $(CFLAGS) src/Processor.cpp

Logger.o : Logger.o src/Logger.cpp
	$(CC) $(CFLAGS) src/Logger.cpp

Metadata.o : Metadata.o src/Metadata.cpp
	$(CC) $(CFLAGS) src/Metadata.cpp

Simulation.o : Simulation.o src/Simulation.cpp
	$(CC) $(CFLAGS) src/Simulation.cpp


clean:
	\rm *.o SimO1

