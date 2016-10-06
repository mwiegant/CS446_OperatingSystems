#ifndef OPERATING_SYSTEM_SIMULATION_H
#define OPERATING_SYSTEM_SIMULATION_H

#define NULL nullptr

#include <cstdio>
#include <string>
#include <fstream>
#include <vector>
#include <queue>

#include "Structures.h"

#include "ConfigFileParser.h"
#include "MetaFileParser.h"
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

    // functions for processing instructions
    void processInstructions();
    int getCycleTime(char code, string descriptor);

    // Configuration Information
    float osVersion;
    char mdf_filePath[50];
    string cpuSchedulingCode;

    // Processing Times
    int processorCycleTime;
    int monitorDisplayTime;
    int hardDriveCycleTime;
    int printerCycleTime;
    int keyboardCycleTime;
    int memoryCycleTime;
    int systemMemory;

    // Log File
    bool logToMonitor;
    bool logToFile;
    string logFileName;
    string logFilePath;

    // Logging Object
    Logger *logger;

    // Queue for holding instructions
    queue<Instruction> instructionsQueue;
};

#endif //OPERATING_SYSTEM_SIMULATION_H
