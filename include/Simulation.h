#ifndef OPERATING_SYSTEM_SIMULATION_H
#define OPERATING_SYSTEM_SIMULATION_H

#include <cstdio>
#include <string>

using namespace std;

class Simulation
{
  public:
    Simulation();
    ~Simulation();
    bool readInConfig(string filePath);
    string getMetadataFilePath();

    // Utility Functions
    void showSimulationSettings();

  private:
    float osVersion;
    string mdf_filePath;
    string cpuSchedulingCode;

    // Processing Times
    int processorCycleTime;
    int monitorDisplayTime;
    int hardDriveCycleTime;
    int printerCycleTime;
    int keyboardCycleTime;

    // Log File
    bool logToFile;
    string logfilePath;


};

#endif //OPERATING_SYSTEM_SIMULATION_H
