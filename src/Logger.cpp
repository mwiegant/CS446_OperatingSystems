#include "Logger.h"

Logger::Logger()
{
  // initialize logging flags
  logToMonitor = false;
  logToFile = false;
}

Logger::~Logger()
{
  // close the file stream
  fileOutStream.close();
}


/*
 * Enable the logger to write messages to the console
 */
void Logger::enableMonitorLogging()
{
  logToMonitor = true;
}


/*
 * Enable the logger to write messages to a file
 */
void Logger::enableLoggingToFile(string filePath)
{
  logToFile = true;

  // setup the connection to log to file
  fileOutStream.clear();
  fileOutStream.open(filePath.c_str());
}


/*
 * Log messages to either the monitor, a file, or both
 */
void Logger::log(string message)
{
  // check if neither logging functionality is enabled
  if(!logToMonitor && !logToFile)
  {
    cout << "err - asked to log when should not log anything to anywhere because no logging mode has been enabled" << endl;
  }

  // check if monitor logging is enabled
  if(logToMonitor)
  {
    // log the message to the monitor
    cout << message << endl;
  }

  // check if file logging is enabled
  if(logToFile)
  {
    // log the message to the file
    fileOutStream << message << endl;
  }
}





