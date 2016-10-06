#include "Simulation.h"

Simulation::Simulation()
{
  osVersion = 0.0f;
  cpuSchedulingCode = "";

  cycleTimes.processorCycleTime = 0;
  cycleTimes.monitorDisplayTime = 0;
  cycleTimes.hardDriveCycleTime = 0;
  cycleTimes.printerCycleTime = 0;
  cycleTimes.keyboardCycleTime = 0;
  cycleTimes.memoryCycleTime = 0;
  systemMemory = 0;

  logToMonitor = false;
  logToFile = false;
  logFileName = "";
  logFilePath = "";

  logger = new Logger();
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
  configFileParser->getProcessorCycleTime( cycleTimes.processorCycleTime );
  configFileParser->getMonitorCycleTime( cycleTimes.monitorDisplayTime );
  configFileParser->getHardDriveCycleTime( cycleTimes.hardDriveCycleTime );
  configFileParser->getPrinterCycleTime( cycleTimes.printerCycleTime );
  configFileParser->getKeyboardCycleTime( cycleTimes.keyboardCycleTime );
  configFileParser->getMemoryCycleTime( cycleTimes.memoryCycleTime );
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

  return true;
}


/*
 * Kicks off the entire simulation, including:
 *  - creating processes from the set of meta instructions
 *  - running each process until their completion (or interruption)
 */
bool Simulation::Run()
{

  createProcesses();

  // run through each process
  while( processes.size() > 0 )
  {
    // run the first process
    processes[0].Run();

    // remove the first process after it finishes running
    processes.erase( processes.begin() );
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

  // log processor settings
  message = "Processor = " + to_string(cycleTimes.processorCycleTime) + " ms/cycle";
  logger->log(message);

  // log monitor settings
  message = "Monitor = " + to_string(cycleTimes.monitorDisplayTime) + " ms/cycle";
  logger->log(message);

  // log hard drive settings
  message = "Hard Drive = " + to_string(cycleTimes.hardDriveCycleTime) + " ms/cycle";
  logger->log(message);

  // log printer settings
  message = "Printer = " + to_string(cycleTimes.printerCycleTime) + " ms/cycle";
  logger->log(message);

  // log keyboard settings
  message = "Keyboard = " + to_string(cycleTimes.keyboardCycleTime) + " ms/cycle";
  logger->log(message);

  // log memory settings
  message = "Memory = " + to_string(cycleTimes.memoryCycleTime) + " ms/cycle";
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



void Simulation::createProcesses()
{
  queue<Instruction> processQueue;
  Instruction instruction;
  Process* process;

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
      process = new Process(cycleTimes, logger, processQueue);

      processes.push_back( *process );

      // empty the process queue, for the next process
      while( !processQueue.empty() )
      {
        processQueue.pop();
      }

    }

  }

}





/*
void Simulation::processInstructions()
{
  // fields for the metadata
  Instruction instruction;
  string descriptor;
  string message;
  char code;
  int cycles;
  int timePerCycle;
  int totalTime;

  // log metadata metrics
  logger->log("Meta-Data Metrics");

  // log metadata instructions while there are instructions to log
  while( !instructionsQueue.empty() )
  {

    // fetch the next instruction
    instruction = instructionsQueue.front();

    // remove the instruction now that it's been fetched
    instructionsQueue.pop();

    // update parameters with the values stored in the instruction
    code = instruction.code;
    descriptor = instruction.descriptor;
    cycles = instruction.cycles;

    // get the time per cycle for the code-descriptor combination
//    timePerCycle = getCycleTime(code, descriptor);

    // compute the total time to process the instruction
    totalTime = cycles * timePerCycle;

    // check if total time is greater than 0
    if( totalTime > 0 )
    {
      // set the message to be empty
      message = "";

      // build the first part of the message
      message += code;
      message += "(" + descriptor + ")" + to_string(cycles);

      // build the second part of the message
      message += " - ";

      // build the third part of the message
      message += to_string(totalTime) + " ms";

      // log the message
      logger->log(message);
    }

  }

}
*/







