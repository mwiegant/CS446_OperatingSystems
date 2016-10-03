# Max Wiegant
# 9 - 10 - 16
# Make Peace, not Bugs

CC = g++
DEBUG = -g
CFLAGS = -Wall -c
LFLAGS = -Wall
SOURCE = ../src/

SimO1 : $(SOURCE)main.cpp Logger.o Simulation.o MetaFileParser.o ConfigFileParser.o FileParser.o
	$(CC) $(LFLAGS) $(SOURCE)main.cpp Logger.o Simulation.o MetaFileParser.o ConfigFileParser.o FileParser.o -o Sim01

Logger.o : Logger.o $(SOURCE)Logger.cpp
	$(CC) $(CFLAGS) $(SOURCE)Logger.cpp

Simulation.o : Simulation.o $(SOURCE)Simulation.cpp
	$(CC) $(CFLAGS) $(SOURCE)Simulation.cpp

MetaFileParser.o : MetaFileParser.o $(SOURCE)MetaFileParser.cpp
	$(CC) $(CFLAGS) $(SOURCE)MetaFileParser.cpp

ConfigFileParser.o : ConfigFileParser.o $(SOURCE)ConfigFileParser.cpp
	$(CC) $(CFLAGS) $(SOURCE)ConfigFileParser.cpp

FileParser.o : FileParser.o $(SOURCE)FileParser.cpp
	$(CC) $(CFLAGS) $(SOURCE)FileParser.cpp

clean:
	\rm *.o simOX

