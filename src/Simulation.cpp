#include "Simulation.h"

Simulation::Simulation()
{
  osVersion = 0.0f;
  cpuSchedulingCode = "";

  settings.processorCycleTime = 0;
  settings.monitorDisplayTime = 0;
  settings.hardDriveCycleTime = 0;
  settings.printerCycleTime = 0;
  settings.keyboardCycleTime = 0;
  settings.memoryCycleTime = 0;
  settings.systemMemory = 0;

  // new settings, since assignment 3
  settings.memoryBlockSize = 0;   //todo - is a default value of 0 going to cause any problems with assigning memory in Processes?
  settings.hardDriveQuantity = 1;
  settings.printerQuantity = 1;
  settings.keyboardQuantity = 1;

  logToMonitor = false;
  logToFile = false;
  logFileName = "";
  logFilePath = "";

  logger = new Logger();
  resourceManager = new ResourceManager(3); // where 3 is the number of unique resource types in this simulation
}

Simulation::~Simulation()
{
  delete logger;
  delete resourceManager;
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
  MetaFileParser* metaFileParser = new MetaFileParser();

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
  configFileParser->getProcessorCycleTime( settings.processorCycleTime );
  configFileParser->getMonitorCycleTime( settings.monitorDisplayTime );
  configFileParser->getHardDriveCycleTime( settings.hardDriveCycleTime );
  configFileParser->getPrinterCycleTime( settings.printerCycleTime );
  configFileParser->getKeyboardCycleTime( settings.keyboardCycleTime );
  configFileParser->getMemoryCycleTime( settings.memoryCycleTime );
  configFileParser->getSystemMemory( settings.systemMemory );
  configFileParser->getLoggingInformation( logToMonitor, logToFile, logFileName, logFilePath);
  configFileParser->getMemoryBlockSize( settings.memoryBlockSize );
  configFileParser->getDeviceQuantities( settings.hardDriveQuantity, settings.printerQuantity, settings.keyboardQuantity);

  // initialize the logger
  if( !logger->Initialize(logToMonitor, logToFile, logFilePath, true) )
  {
    printf("Error - failed to initialize the logger.\n");
    return false;
  }

  // initialize the resource manager
  if( !resourceManager->Initialize(settings.hardDriveQuantity, settings.printerQuantity, settings.keyboardQuantity,
                                    settings.systemMemory, settings.memoryBlockSize) )
  {
    printf("Error - failed to iniitialize the resource manager.\n");
    return false;
  }

  // log the configuration of the simulation
  logSimulationSettings();

  // read in the metadata file
  if( !metaFileParser->readInMetadata(mdf_filePath, instructionsQueue) )
  {
    printf("Error - failed to read in the metadata file at %s.\n", mdf_filePath);
    return false;
  }

  // clean up file parsing objects
  delete configFileParser;
  delete metaFileParser;

  configFileParser = NULL;
  metaFileParser = NULL;

  logger->log("test..test..test");

  return true;
}


/*
 * Kicks off the entire simulation, including:
 *  - creating processes from the set of meta instructions
 *
 *  - running each process until their completion (or interruption)
 */
bool Simulation::Run()
{
  // for determining which process is running
  int processCounter = 1;
  timeval startTime;

  // get the time
  gettimeofday( &startTime, NULL );

  // divide the master queue of instructions into smaller queues inside processes
  createProcesses();

  logger->log("Meta-Data Metrics");

  // run through each process
  while( readyQueue.size() > 0 )
  {
    // dequeue the first process from the ready queue
    runningProcess = &(readyQueue.front());

    // run the first process
    runningProcess->Run( startTime );

    readyQueue.pop();

    // increment process counter
    processCounter++;
  }

  return true;
}


/*
 * Output all settings from the simulation to the console.
 */
void Simulation::logSimulationSettings()
{
  string message;

  // begin logging to the file
  logger->log("Configuration File Data");

  // log system memory
  message = "System memory = " + to_string(settings.systemMemory) + " (kbytes)";
  logger->log(message);

  // log memory block size
  message = "Memory block size = " + to_string(settings.memoryBlockSize) + " (kbytes)";
  logger->log(message);

  // log processor settings
  message = "Processor = " + to_string(settings.processorCycleTime) + " ms/cycle";
  logger->log(message);

  // log monitor settings
  message = "Monitor = " + to_string(settings.monitorDisplayTime) + " ms/cycle";
  logger->log(message);

  // log hard drive settings
  message = "Hard Drive = " + to_string(settings.hardDriveCycleTime) + " ms/cycle";
  logger->log(message);

  // log printer settings
  message = "Printer = " + to_string(settings.printerCycleTime) + " ms/cycle";
  logger->log(message);

  // log keyboard settings
  message = "Keyboard = " + to_string(settings.keyboardCycleTime) + " ms/cycle";
  logger->log(message);

  // log memory settings
  message = "Memory = " + to_string(settings.memoryCycleTime) + " ms/cycle";
  logger->log(message);

  message = "Hard Drives: " + to_string(settings.hardDriveQuantity);
  logger->log(message);

  message = "Printers: " + to_string(settings.printerQuantity);
  logger->log(message);

  message = "Keyboards: " + to_string(settings.keyboardQuantity);
  logger->log(message);

  // setup the message to log the settings on where the simulation is logging
  message = "Logged to: ";

  if(logToMonitor && logToFile)
  {
//    message += "monitor and " + logFileName;
    message += "monitor";
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



void Simulation::createProcesses()
{
  queue<Instruction> processQueue;
  Instruction instruction;
  Process* process;
  int processId = 1;

  while( !instructionsQueue.empty() )
  {
    // remove item from the queue
    instruction = instructionsQueue.front();
    instructionsQueue.pop();

    // add item to the new process's queue
    processQueue.push(instruction);

    // enqueue instructions into the new process queue until A(end)0 is encountered
    if( instruction.code == 'A' && instruction.descriptor == "end" )
    {

      // if the instructions queue only has 1 item left (ie, S(end)0 ), just enqueue it here
      if( instructionsQueue.size() == 1 )
      {
        instruction = instructionsQueue.front();
        instructionsQueue.pop();
        processQueue.push(instruction);
      }

      // create a new process
      process = new Process(processId, settings, logger, resourceManager, processQueue);

      readyQueue.push( *process );

      // empty the process queue, for the next process
      while( !processQueue.empty() )
      {
        processQueue.pop();
      }

    }

  }

}









