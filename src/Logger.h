#ifndef OPERATING_SYSTEM_LOGGER_H
#define OPERATING_SYSTEM_LOGGER_H

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Logger
{
  public:
    Logger();
    ~Logger();

    void enableMonitorLogging();
    void enableLoggingToFile(string filename);
    void log(string message);

  private:

    ofstream fileOutStream;
    bool logToMonitor;
    bool logToFile;
};

#endif //OPERATING_SYSTEM_LOGGER_H
