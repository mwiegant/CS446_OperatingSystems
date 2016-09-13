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
    bool readInConfig(char filePath[]);
    string getMetadataFilePath();

    // Utility Functions
    void showSimulationSettings();

  private:
    // Private Functions
    void splitString(string theString, char delimiter, vector<string> &theSplitString);
    void extractData(string fileData);
    void processData(string label, string data);



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
