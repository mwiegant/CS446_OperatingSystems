# Max Wiegant
# 9 - 10 - 16
# Make Peace, not Bugs

CC = g++
DEBUG = -g
CFLAGS = -Wall -c
LFLAGS = -Wall
SOURCE = ../src/

SimO1 : $(SOURCE)main.cpp Processor.o Logger.o Metadata.o Simulation.o ConfigFileParser.o FileParser.o
	$(CC) $(LFLAGS) $(SOURCE)main.cpp Processor.o Logger.o Metadata.o Simulation.o ConfigFileParser.o FileParser.o -o Sim01

Processor.o : Processor.o $(SOURCE)Processor.cpp
	$(CC) $(CFLAGS) $(SOURCE)Processor.cpp

Logger.o : Logger.o $(SOURCE)Logger.cpp
	$(CC) $(CFLAGS) $(SOURCE)Logger.cpp

Metadata.o : Metadata.o $(SOURCE)Metadata.cpp
	$(CC) $(CFLAGS) $(SOURCE)Metadata.cpp

Simulation.o : Simulation.o $(SOURCE)Simulation.cpp
	$(CC) $(CFLAGS) $(SOURCE)Simulation.cpp

ConfigFileParser.o : ConfigFileParser.o $(SOURCE)ConfigFileParser.cpp
	$(CC) $(CFLAGS) $(SOURCE)ConfigFileParser.cpp

FileParser.o : FileParser.o $(SOURCE)FileParser.cpp
	$(CC) $(CFLAGS) $(SOURCE)FileParser.cpp

clean:
	\rm *.o simOX

