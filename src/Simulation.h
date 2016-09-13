#ifndef OPERATING_SYSTEM_SIMULATION_H
#define OPERATING_SYSTEM_SIMULATION_H

#include <cstdio>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>

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

    // Utility Function
    void showSimulationSettings();

    bool readInConfig(char filePath[]);

  private:
    // for extracting and parsing in the config file
    void extractData(string fileData);
    void processData(string label, string data);

    // additional helper function for parsing
    void splitString(string theString, char delimiter, vector<string> &theSplitString);

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
    bool logToConsole;
    bool logToFile;
    string logFilePath;


};

#endif //OPERATING_SYSTEM_SIMULATION_H
