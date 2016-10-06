#ifndef OPERATING_SYSTEM_SIMULATION_H
#define OPERATING_SYSTEM_SIMULATION_H

#include <cstdio>
#include <string>
#include <fstream>
#include <vector>
#include <queue>

#include "Structures.h"

#include "ConfigFileParser.h"
#include "MetaFileParser.h"
#include "Process.h"
#include "Logger.h"

using namespace std;

class Simulation
{
  public:
    Simulation();
    ~Simulation();

    bool Initialize(char filePath[]);
    bool Run();

  private:
    void logSimulationSettings();

    // splits instructions among processes
    void createProcesses();

    // todo - deprecate this function - move into Process
//    void processInstructions();


    // Configuration Information
    float osVersion;
    int systemMemory;
    char mdf_filePath[50];
    string cpuSchedulingCode;

    // Processing Times
    SimCycleTimes cycleTimes;

    // Log File
    bool logToMonitor;
    bool logToFile;
    string logFileName;
    string logFilePath;

    // Logging Object
    Logger *logger;

    // Vector for holding processes
    vector<Process> processes;

    // Queue for holding instructions
    queue<Instruction> instructionsQueue;
};

#endif //OPERATING_SYSTEM_SIMULATION_H
