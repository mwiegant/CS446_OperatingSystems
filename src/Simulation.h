#ifndef OPERATING_SYSTEM_SIMULATION_H
#define OPERATING_SYSTEM_SIMULATION_H

#include <cstdio>
#include <string>
#include <fstream>
#include <vector>

#include "Logger.h"

using namespace std;

class Simulation
{
  public:
    Simulation();
    ~Simulation();

    // Getters
    string getMetadataFilePath();
    int getProcessorCycleTime();
    int getMonitorDisplayTime();
    int getHardDriveCycleTime();
    int getPrinterCycleTime();
    int getKeyboardCycleTime();
    int getMemoryCycleTime();

    // Configuration Functions
    void setLogger(Logger *theLogger);
    bool readInConfig(char filePath[]);

  private:
    // for extracting and parsing in the config file
    void extractData(string fileData);
    void processData(string label, string data);

    // Additional Parser Helper Functions
    void splitString(string theString, char delimiter, vector<string> &theSplitString);

    // Logger Interaction Functions
    void turnLoggerOn();
    void logSimulationSettings();

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
    string logFilePath;

    // Logging Object
    Logger *logger;
};

#endif //OPERATING_SYSTEM_SIMULATION_H
