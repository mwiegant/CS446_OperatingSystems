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
 * Set up the logger with where to log to. If 'clearTheFile' is set to true, the specified
 * file will be cleared. If clearing the file fails, a warning will be printed to the screen.
 */
bool Logger::Initialize(bool logToMonitor, bool logToFile, string filePath, bool clearTheFile)
{
  this->logToMonitor = logToMonitor;
  this->logToFile = logToFile;


  strcpy( this->filePath, filePath.c_str() );

  printf("filepath: %s\n", this->filePath);

  // clear the file by writing to it
  if(clearTheFile)
  {
    fileOutStream.clear();
    fileOutStream.open( this->filePath );

    if( fileOutStream.good() )
    {
      fileOutStream << "";
    }
    else
    {
      printf("Warning - failed to clear the file\n");
    }
  }


  return true;
}


/*
 * Log messages to either the monitor, a file, or both
 */
void Logger::log(string message)
{
  // check if neither logging functionality is enabled
  if(!logToMonitor && !logToFile)
  {
    printf("Error - asked to log when no logging mode has been enabled\n");
  }

  if(logToMonitor)
  {
    printf("%s\n", message.c_str());
  }

  if(logToFile)
  {
    // log the message to the file
    writeToFile(message.c_str());
  }
}


bool Logger::writeToFile(const char* message)
{
  bool successfulWrite = false;

  // clear and open the file in append mode
  fileOutStream.clear();
  fileOutStream.open(filePath, fstream::app);

  if( fileOutStream.good() )
  {
    successfulWrite = true;

    fileOutStream << message << endl;
  }

  // close the file stream
  fileOutStream.close();

  return successfulWrite;
}




