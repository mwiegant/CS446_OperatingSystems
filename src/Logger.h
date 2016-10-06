#ifndef OPERATING_SYSTEM_LOGGER_H
#define OPERATING_SYSTEM_LOGGER_H

#include <cstdio>
#include <fstream>
#include <cstring>
#include <string>

using namespace std;

class Logger
{
  public:
    Logger();
    ~Logger();

    bool Initialize(bool logToMonitor, bool logToFile, string filePath, bool clearTheFile);
    void log(string message);

  private:
    bool writeToFile(const char* message);

    ofstream fileOutStream;
    char filePath[50];
    bool logToMonitor;
    bool logToFile;
};

#endif //OPERATING_SYSTEM_LOGGER_H
