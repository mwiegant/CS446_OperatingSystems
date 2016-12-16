#include "Simulation.h"

Simulation::Simulation()
{
  osVersion = 0.0f;
  cpuSchedulingCode = "";
  defaultQuantumNumber = 1;

  settings.processorCycleTime = 0;
  settings.monitorDisplayTime = 0;
  settings.hardDriveCycleTime = 0;
  settings.printerCycleTime = 0;
  settings.keyboardCycleTime = 0;
  settings.memoryCycleTime = 0;
  settings.systemMemory = 0;

  // new settings, since assignment 3
  settings.memoryBlockSize = 128;
  settings.hardDriveQuantity = 1;
  settings.printerQuantity = 1;

  logToMonitor = false;
  logToFile = false;
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
  configFileParser->getSchedulingData( cpuSchedulingCode, defaultQuantumNumber );
  configFileParser->getProcessorCycleTime( settings.processorCycleTime );
  configFileParser->getMonitorCycleTime( settings.monitorDisplayTime );
  configFileParser->getHardDriveCycleTime( settings.hardDriveCycleTime );
  configFileParser->getPrinterCycleTime( settings.printerCycleTime );
  configFileParser->getKeyboardCycleTime( settings.keyboardCycleTime );
  configFileParser->getMemoryCycleTime( settings.memoryCycleTime );
  configFileParser->getSystemMemory( settings.systemMemory );
  configFileParser->getLoggingInformation( logToMonitor, logToFile, logFilePath);
  configFileParser->getMemoryBlockSize( settings.memoryBlockSize );
  configFileParser->getDeviceQuantities( settings.hardDriveQuantity, settings.printerQuantity);

  // initialize the logger
  if( !logger->Initialize(logToMonitor, logToFile, logFilePath, true) )
  {
    printf("Error - failed to initialize the logger.\n");
    return false;
  }

  // initialize the resource manager
  if( !resourceManager->Initialize(settings.hardDriveQuantity, settings.printerQuantity,
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
  timeval startTime;

  // load processes into the simulation from the master queue of instructions
  createProcesses();

  // get the time
  gettimeofday( &startTime, NULL );

  logger->log("-----------------------");
  logger->log("-- Meta-Data Metrics");
  logger->log("-----------------------");

  // run the first process once, to get past the first start instruction in this process
  runningProcess = &(readyQueue[0]);

  runningProcess->Run(startTime);

//  // run each process once, to get past the initial start instruction
//  for(int i = 0; i < readyQueue.size(); i++)
//  {
//    runningProcess = &(readyQueue[i]);
//
//    runningProcess->Run(startTime);
//  }

  // run through each process according the the specified algorithm
  if(cpuSchedulingCode == "RR")
  {
    runRR(startTime);
    return true;
  }
  else if(cpuSchedulingCode == "SJF")
  {
    runSFJ(startTime);
    return true;
  }
  else if(cpuSchedulingCode == "SRTF")
  {
    runSRTF(startTime);
    return true;
  }
  else
  {
    logger->log("Error - Invalid Scheduling Code. Valid codes are 'RR', 'SJF', or 'SRTF'");
    return false;
  }
}


/*
 * Runs processes in a Round-Robin fashion. Each process is given a chance to run
 * before the next process is then ran. This cycle continues until all processes have
 * finished running all their instructions.
 */
void Simulation::runRR(timeval startTime)
{
  vector<int> processRunOrder;
  int processingOrderIndex = 0;
  int currentProcessIndex;

  // determine the processing order
  /// for RR, the processing order is simply in order
  for(int i = 0; i < readyQueue.size(); i ++)
  {
    processRunOrder.push_back(i);
  }

  // run processes until they are done
  while(processRunOrder.size() > 0)
  {
    // get the index of the next process to run
    currentProcessIndex = processRunOrder[processingOrderIndex];

    // get the next process to run
    runningProcess = &(readyQueue[currentProcessIndex]);

    runningProcess->Run(startTime);

    // check if the process is now terminated
    if( runningProcess->getProcessState() == TERMINATED)
    {
      // erase the process from the list of processes to run
      processRunOrder.erase( processRunOrder.begin() + processingOrderIndex);
    }
    else
    {
      processingOrderIndex++;
    }

    // reset the processing order index to 0 as needed
    if(processingOrderIndex >= processRunOrder.size())
    {
      processingOrderIndex = 0;
    }


  }

}


/*
 * Runs processes in a Shortest-Job-First fashion. Runs whichever process has
 * the least cycles in its next instruction. Continually cycles through processes
 * until every process has completed running all its instructions.
 */
void Simulation::runSFJ(timeval startTime)
{
  vector<int> processesRemaining;
  int indexOfShortestJob;
  int leastCycles;
  int index;

  // make a list of all processes
  for(int i = 0; i < readyQueue.size(); i ++)
  {
    processesRemaining.push_back(i);
  }

  // run until there are no processes remaining
  while(processesRemaining.size() > 0)
  {

    // give initial values
    indexOfShortestJob = 0;
    leastCycles = readyQueue[0].getNextInstructionCycles();

    // determine which process to run next
    for(int i = 0; i < processesRemaining.size(); i++)
    {

      index = processesRemaining[i];

      if( readyQueue[index].getNextInstructionCycles() < leastCycles )
      {
        indexOfShortestJob = index;
        leastCycles = readyQueue[index].getNextInstructionCycles();
      }

    }

    // run the process
    runningProcess = &(readyQueue[indexOfShortestJob]);

    runningProcess->Run(startTime);

    // check if the process is now terminated
    if( runningProcess->getProcessState() == TERMINATED)
    {
      // erase the process from the list of processes to run
      processesRemaining.erase( processesRemaining.begin() + indexOfShortestJob);
    }


  }
}


/*
 * Runs processes in a Shortest-Remaining-Time-First fashion. Runs whichever process
 * has the least instructions remaining (which is assumed to be the process that has
 * the shortest time remaining). Continually runs in this way until all processes
 * have finished running their instructions.
 */
void Simulation::runSRTF(timeval startTime)
{
  vector<int> processesRemaining;
  int indexOfShortestJob;
  int leastInstructions;
  int index;

  // make a list of all processes
  for(int i = 0; i < readyQueue.size(); i ++)
  {
    processesRemaining.push_back(i);
  }

  // determine which process to run first
  for(int i = 0; i < processesRemaining.size(); i++)
  {

    index = processesRemaining[i];

    if( readyQueue[index].getInstructionsRemaining() < leastInstructions )
    {
      indexOfShortestJob = index;
      leastInstructions = readyQueue[index].getInstructionsRemaining();
    }
  }

  // run until there are no processes remaining
  while(processesRemaining.size() > 0)
  {
    // run the process
    runningProcess = &(readyQueue[indexOfShortestJob]);

    runningProcess->Run(startTime);

    // check if the process is now terminated
    if( runningProcess->getProcessState() == TERMINATED)
    {
      // erase the process from the list of processes to run
      processesRemaining.erase( processesRemaining.begin() + indexOfShortestJob);

      // determine which process to run next
      for(int i = 0; i < processesRemaining.size(); i++)
      {

        index = processesRemaining[i];

        if( readyQueue[index].getInstructionsRemaining() < leastInstructions )
        {
          indexOfShortestJob = index;
          leastInstructions = readyQueue[index].getInstructionsRemaining();
        }
      }
    }


  }
}


/*
 * Output all settings from the simulation to the console.
 */
void Simulation::logSimulationSettings()
{
  string message;

  // begin logging to the file
  logger->log("-----------------------------");
  logger->log("-- Configuration File Data");
  logger->log("-----------------------------");

  // setup the message to log the settings on where the simulation is logging
  message = "Logged to: ";

  if(logToMonitor && logToFile)
  {
    message += "monitor and " + logFilePath;
  }
  else if(logToMonitor)
  {
    message += "monitor";
  }
  else if(logToFile)
  {
    message += logFilePath;
  }

  // log where the simulation is logging
  logger->log(message);

  // log scheduling data
  message = "Scheduling Algorithm: " + cpuSchedulingCode;
  logger->log(message);

  message = "Default Quantum Number: " + to_string(defaultQuantumNumber);
  logger->log(message);

  // log device quantities
  message = "Hard Drives: " + to_string(settings.hardDriveQuantity);
  logger->log(message);

  message = "Printers: " + to_string(settings.printerQuantity);
  logger->log(message);

  // log system memory
  message = "System memory = " + to_string(settings.systemMemory) + " (kbytes)";
  logger->log(message);

  // log memory block size
  message = "Memory block size = " + to_string(settings.memoryBlockSize) + " (kbytes)";
  logger->log(message);

  // log cycle times
  message = "Processor = " + to_string(settings.processorCycleTime) + " ms/cycle";
  logger->log(message);

  message = "Monitor = " + to_string(settings.monitorDisplayTime) + " ms/cycle";
  logger->log(message);

  message = "Hard Drive = " + to_string(settings.hardDriveCycleTime) + " ms/cycle";
  logger->log(message);

  message = "Printer = " + to_string(settings.printerCycleTime) + " ms/cycle";
  logger->log(message);

  message = "Keyboard = " + to_string(settings.keyboardCycleTime) + " ms/cycle";
  logger->log(message);

  message = "Memory = " + to_string(settings.memoryCycleTime) + " ms/cycle";
  logger->log(message);

  // log an empty line
  logger->log("");
}


/*
 * Separates the master-list of meta-data instructions into separate processes.
 */
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
      process = new Process(processId, defaultQuantumNumber, settings, logger, resourceManager, processQueue);

      readyQueue.push_back( *process );

      processId++;

      // empty the process queue, for the next process
      while( !processQueue.empty() )
      {
        processQueue.pop();
      }

    }

  }

}









