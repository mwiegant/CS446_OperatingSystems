# Max Wiegant
# 9 - 10 - 16
# Make Peace, not Bugs

# todo - link this file into my build directory so I don't have to move it back and forth on commits

CC = g++
DEBUG = -g
CFLAGS = -c -std=c++11 -pthread
LFLAGS = -std=c++11 -pthread
# SOURCE = ../src/
SOURCE = src/

sim02 : $(SOURCE)main.cpp Logger.o Simulation.o Process.o ResourceManager.o MetaFileParser.o ConfigFileParser.o FileParser.o
	$(CC) $(LFLAGS) $(SOURCE)main.cpp Logger.o Simulation.o Process.o ResourceManager.o MetaFileParser.o ConfigFileParser.o FileParser.o -o simO4

Logger.o : $(SOURCE)Logger.cpp
	$(CC) $(CFLAGS) $(SOURCE)Logger.cpp

Simulation.o : $(SOURCE)Simulation.cpp
	$(CC) $(CFLAGS) $(SOURCE)Simulation.cpp

Process.o : $(SOURCE)Process.cpp
	$(CC) $(CFLAGS) $(SOURCE)Process.cpp

ResourceManager.o : $(SOURCE)ResourceManager.cpp
	$(CC) $(CFLAGS) $(SOURCE)ResourceManager.cpp

MetaFileParser.o : $(SOURCE)MetaFileParser.cpp
	$(CC) $(CFLAGS) $(SOURCE)MetaFileParser.cpp

ConfigFileParser.o : $(SOURCE)ConfigFileParser.cpp
	$(CC) $(CFLAGS) $(SOURCE)ConfigFileParser.cpp

FileParser.o : $(SOURCE)FileParser.cpp
	$(CC) $(CFLAGS) $(SOURCE)FileParser.cpp

clean:
	\rm *.o simO4

