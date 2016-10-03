#ifndef OPERATING_SYSTEM_SIMULATION_H
#define OPERATING_SYSTEM_SIMULATION_H

#include <cstdio>
#include <string>
#include <fstream>
#include <vector>

#include "ConfigFileParser.h"
#include "Metadata.h"
#include "Logger.h"

using namespace std;

class Simulation
{
  public:
    Simulation();
    ~Simulation();

    bool Initialize(char filePath[]);
    bool Run(Metadata *metadata);

    // Getters
    string getMetadataFilePath();
    int getCycleTime(char code, string descriptor);

    // Configuration Functions
    void setLogger(Logger *theLogger);

  private:
    void logSimulationSettings();

    void processInstructions(Metadata *metadata);

    // Configuration Information
    float osVersion;
    string mdf_filePath;
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
};

#endif //OPERATING_SYSTEM_SIMULATION_H
