#ifndef OPERATING_SYSTEM_LOGGER_H
#define OPERATING_SYSTEM_LOGGER_H

/*
 * CLASS - Logger
 *
 * ABOUT - Dedicated logging class. Handles logging to a file
 *  and monitor, as specified. For file logging, appends messages
 *  to the file as they are received by the logger.
 */

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