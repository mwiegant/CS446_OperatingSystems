#ifndef OPERATING_SYSTEM_SIMULATION_H
#define OPERATING_SYSTEM_SIMULATION_H

/*
 * CLASS - Simulation
 *
 * ABOUT - Driver class for running the entire operating system.
 *   Loads in the config file and metadata file using their appropriate
 *   file parsers. Sets up the logger object and it's logging mode(s).
 *   Finally, sets up processes and provides a function to run them.
 */

#include <time.h>
#include <sys/time.h>
#include <cstdio>
#include <string>
#include <fstream>
#include <vector>
#include <queue>

#include "Structures.h"

#include "ConfigFileParser.h"
#include "MetaFileParser.h"
#include "ResourceManager.h"
#include "Process.h"
#include "Logger.h"

using namespace std;

class Simulation
{
  public:
    Simulation();
    ~Simulation();

    bool Initialize(char filePath[]);

    // used to begin running meta instructions
    bool Run();

  private:
    void logSimulationSettings();

    // splits instructions among processes
    void createProcesses();

    // for initializing mutexes and semaphores
    void initializeSyncDevices();

    // for running with different scheduling algorithms
    void runRR(timeval startTime);
    void runSFJ(timeval startTime);
    void runSRTF(timeval startTime);

    // Configuration Information
    float osVersion;
    char mdf_filePath[50];
    string cpuSchedulingCode;
    int defaultQuantumNumber;

    // Processing Times
    SimulatorSettings settings;

    // Log File
    bool logToMonitor;
    bool logToFile;
    string logFilePath;

    // Logging Object
    Logger *logger;

    // Resource Manager
    ResourceManager* resourceManager;

    // Queue for holding instructions
    queue<Instruction> instructionsQueue;

    // Queues for PCB implementation
    Process* runningProcess;
    vector<Process> readyQueue;

};

#endif //OPERATING_SYSTEM_SIMULATION_H
