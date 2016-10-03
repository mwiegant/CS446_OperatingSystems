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
  memoryCycleTime = 0;
  systemMemory = 0;

  logToMonitor = false;
  logToFile = false;
  logFileName = "";
  logFilePath = "";
}

Simulation::~Simulation()
{

}


/*
 * Handles initialization of the Operating System, which includes:
 *  - reading in the configuration file
 *  - reading in the metadata file
 *  - initializing the logger
 */
bool Simulation::Initialize(char filePath[])
{
  ConfigFileParser* configFileParser = new ConfigFileParser();


  // read in the config file
  if( !configFileParser->readInConfig(filePath) )
  {
    printf("Error - failed to read in the config file at %s.\n", filePath);
    return false;
  }

  // get values from the config file parser
  configFileParser->getOSVersion( osVersion );
  configFileParser->getMetaFilePath( mdf_filePath );
  configFileParser->getSchedulingCode( cpuSchedulingCode );
  configFileParser->getProcessorCycleTime( processorCycleTime );
  configFileParser->getMonitorCycleTime( monitorDisplayTime );
  configFileParser->getHardDriveCycleTime( hardDriveCycleTime );
  configFileParser->getPrinterCycleTime( printerCycleTime );
  configFileParser->getKeyboardCycleTime( keyboardCycleTime );
  configFileParser->getMemoryCycleTime( memoryCycleTime );
  configFileParser->getSystemMemory( systemMemory );
  configFileParser->getLoggingInformation( logToMonitor, logToFile, logFileName, logFilePath);

  // initialize the logger
  if( !logger->Initialize(logToMonitor, logToFile, logFilePath, true) )
  {
    printf("Error - failed to initialize the logger.\n");
    return false;
  }

  // log the configuration of the simulation
  logSimulationSettings();


  // clean up file parsing objects
  delete configFileParser;

  return true;
}



/*
 * Get the path for the metadata file
 */
string Simulation::getMetadataFilePath()
{
  return mdf_filePath;
}


/*
 * Get the desired cycle time for a device based on
 * the code and the descriptor provided
 */
int Simulation::getCycleTime(char code, string descriptor)
{
  int cycleTime = 0;

  // determine which cycle time to return, based on the code
  switch(code)
  {
    // case P
    case 'P':

      if( descriptor == "run" )
      {
        cycleTime = processorCycleTime;
      }
      break;

    // case I
    case 'I':

      if( descriptor == "hard drive" )
      {
        cycleTime = hardDriveCycleTime;
      }
      else if( descriptor == "monitor")
      {
        cycleTime = monitorDisplayTime;
      }
      else if( descriptor == "keyboard")
      {
        cycleTime = keyboardCycleTime;
      }
      break;

    // case O
    case 'O':

      if( descriptor == "hard drive" )
      {
        cycleTime = hardDriveCycleTime;
      }
      else if( descriptor == "monitor")
      {
        cycleTime = monitorDisplayTime;
      }
      else if( descriptor == "printer" )
      {
        cycleTime = printerCycleTime;
      }
      break;

    // case M
    case 'M':

      if( descriptor == "allocate" )
      {
        cycleTime = memoryCycleTime;
      }
      else if( descriptor == "cache")
      {
        cycleTime = memoryCycleTime;
      }
      break;
  }

  return cycleTime;
}


/*
 * Provide a logger for output within this class
 */
void Simulation::setLogger(Logger *theLogger)
{
  logger = theLogger;
}


/*
 * Output all settings from the simulation to the console
 */
void Simulation::logSimulationSettings()
{
  string message;

  // begin logging to the file
  logger->log("Configuration File Data");

  // log processor settings
  message = "Processor = " + to_string(processorCycleTime) + " ms/cycle";
  logger->log(message);

  // log monitor settings
  message = "Monitor = " + to_string(monitorDisplayTime) + " ms/cycle";
  logger->log(message);

  // log hard drive settings
  message = "Hard Drive = " + to_string(hardDriveCycleTime) + " ms/cycle";
  logger->log(message);

  // log printer settings
  message = "Printer = " + to_string(printerCycleTime) + " ms/cycle";
  logger->log(message);

  // log keyboard settings
  message = "Keyboard = " + to_string(keyboardCycleTime) + " ms/cycle";
  logger->log(message);

  // log memory settings
  message = "Memory = " + to_string(memoryCycleTime) + " ms/cycle";
  logger->log(message);

  // setup the message to log the settings on where the simulation is logging
  message = "Logged to: ";

  if(logToMonitor && logToFile)
  {
    message += "monitor and " + logFileName;
  }
  else if(logToMonitor)
  {
    message += "monitor";
  }
  else if(logToFile)
  {
    message += logFileName;
  }

  // finally, log where the simulation is logging
  logger->log(message);

  // log an empty line
  logger->log("");
}

