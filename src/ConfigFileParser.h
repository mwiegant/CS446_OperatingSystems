#ifndef OPERATING_SYSTEM_CONFIGFILEPARSER_H
#define OPERATING_SYSTEM_CONFIGFILEPARSER_H

#include <vector>
#include <string>
#include <cstdio>

#include "FileParser.h"

using namespace std;

class ConfigFileParser: public FileParser
{
  public:
    ConfigFileParser();
    ~ConfigFileParser();

    bool readInConfig(char filePath[]);

    // getters
    void getOSVersion(float& osVersion);
    void getMetaFilePath(string& metaFilePath);
    void getSchedulingCode(string& schedulingCode);
    void getProcessorCycleTime(int& cycleTime);
    void getMonitorCycleTime(int& cycleTime);
    void getHardDriveCycleTime(int& cycleTime);
    void getPrinterCycleTime(int& cycleTime);
    void getKeyboardCycleTime(int& cycleTime);
    void getMemoryCycleTime(int& cycleTime);
    void getSystemMemory(int& systemMemory);
    void getLoggingInformation(bool& logToMonitor, bool& logToFile, string& logFileName, string& logFilePath);

  private:
    // for extracting and parsing in the config file
    void extractData(string fileData);
    void processData(string label, string data);

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
};

#endif //OPERATING_SYSTEM_CONFIGFILEPARSER_H