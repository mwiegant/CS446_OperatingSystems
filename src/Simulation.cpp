#include "Simulation.h"

Simulation::Simulation()
{
  osVersion = 0.0f;
  mdf_filePath = "";
  cpuSchedulingCode = "";

  processorCycleTime = 0;
  monitorDisplayTime = 0;
  hardDriveCycleTime = 0;
  printerCycleTime = 0;
  keyboardCycleTime = 0;

  logToFile = false;
  logfilePath = "";
}

Simulation::~Simulation()
{

}

bool Simulation::readInConfig(string filePath)
{
  // todo

  return false;
}

/*
 * Return the path to the metadata file, as found in the configuration file
 */
string Simulation::getMetadataFilePath()
{
  return mdf_filePath;
}

/*
 * Output all settings from the simulation to the console
 */
void Simulation::showSimulationSettings()
{
  fprintf(stdout, "Simulation Settings\n");
  fprintf(stdout, "-------------------\n\n");
  fprintf(stdout, "osVersion          : %f\n", osVersion);
  fprintf(stdout, "msf_filePath       : %s\n", mdf_filePath.c_str());
  fprintf(stdout, "cpuSchedulingCode  : %s\n", cpuSchedulingCode.c_str());
  fprintf(stdout, "processorCycleTime : %d\n", processorCycleTime);
  fprintf(stdout, "monitorDisplayTime : %d\n", monitorDisplayTime);
  fprintf(stdout, "hardDriveCycleTime : %d\n", hardDriveCycleTime);
  fprintf(stdout, "printerCycleTime   : %d\n", printerCycleTime);
  fprintf(stdout, "keyboardCycleTime  : %d\n", keyboardCycleTime);
  fprintf(stdout, "processorCycleTime : %d\n", processorCycleTime);
  fprintf(stdout, "logToFile          : %d\n", logToFile);
  fprintf(stdout, "logfilePath        : %s\n", logfilePath.c_str());

}

/*
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

 */