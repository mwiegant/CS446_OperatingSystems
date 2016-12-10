#ifndef OPERATING_SYSTEM_CONFIGFILEPARSER_H
#define OPERATING_SYSTEM_CONFIGFILEPARSER_H

/*
 * CLASS - ConfigFIleParser
 *
 * ABOUT - Dedicated class for reading in and parsing from
 *  the configuration file. Reads in all the information from
 *  the file and makes it accessible via getter functions.
 */

// todo - fix known bug - program doesn't log correctly when told to only log to file

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
    void getMetaFilePath(char metaFilePath[]);
    void getSchedulingCode(string& schedulingCode);
    void getProcessorCycleTime(int& cycleTime);
    void getMonitorCycleTime(int& cycleTime);
    void getHardDriveCycleTime(int& cycleTime);
    void getPrinterCycleTime(int& cycleTime);
    void getKeyboardCycleTime(int& cycleTime);
    void getMemoryCycleTime(int& cycleTime);
    void getSystemMemory(int& systemMemory);
    void getLoggingInformation(bool& logToMonitor, bool& logToFile, string& logFilePath);
    void getMemoryBlockSize(int& blockSize);
    void getDeviceQuantities(int& numHardDrives, int& numPrinters, int& numKeyboards);

  private:
    // for extracting and parsing in the config file
    void extractData(string fileData);
    void processData(string label1, string label2, string data);

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

    // Memory block size and device quantities
    int memoryBlockSize;
    int hardDriveQuantity;
    int printerQuantity;
    int keyboardQuantity;

    // Log File
    bool logToMonitor;
    bool logToFile;
    string logFilePath;
};

#endif //OPERATING_SYSTEM_CONFIGFILEPARSER_H
