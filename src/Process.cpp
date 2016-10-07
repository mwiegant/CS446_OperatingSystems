#include "Process.h"

/*
 * ===============================================================================
 * ========================>  HELPER FUNCTIONS  <========================
 * ===============================================================================
 */

/*
 * Returns how much time has passed since the reference time.
 */
int timePassed( struct timeval refTime )
{
  timeval currentTime;
  int microsec, seconds;

  gettimeofday( &currentTime, NULL );
  seconds = currentTime.tv_sec - refTime.tv_sec;
  microsec = currentTime.tv_usec - refTime.tv_usec;

  if( microsec < 0 )
  {
    microsec += 1000000;
    seconds -= 1;
  }

  if( seconds > 0 )
  {
    microsec = microsec + ( seconds * 1000000 );
  }

  return microsec;
}


/*
 * Simulates memory allocation by returning a random number.
 */
unsigned int allocateMemory( int totalMemory )
{
  unsigned int address = 0;

  srand(time(NULL));

  if( totalMemory > 0 )
  {
    address = rand() % totalMemory;
  }
  return address;
}


/*
 * Meant to be used by threads.
 *
 * Takes in a wait time, and doesn't exit from the thread
 * until the wait time has expired.
 */
void* threadRunner(void* _waitTime)
{
  int* waitTime = (int*) _waitTime;

  struct timeval referenceTime;

  gettimeofday( &referenceTime, NULL );

  while( timePassed(referenceTime) < *waitTime );

  pthread_exit(0);
}


/*
 * ===============================================================================
 * ========================>  CLASS IMPLEMENTATION  <========================
 * ===============================================================================
 */

Process::Process(SimulatorSettings simulatorSettings, Logger* logger, queue<Instruction> instructionsQueue )
{
  this->simulatorSettings = simulatorSettings;
  this->logger = logger;
  this->instructionsQueue = instructionsQueue;

  // set default state to ready
  processState = READY;

  this->logger->log("successfully created a new process!!!");
}


Process::~Process()
{

}


/*
 * Cycles through all instructions in this process
 */
void Process::Run()
{
  char code;
  string descriptor;
  Instruction instruction;
  int cycles, timePerCycle, runTime;
  bool stillRunning = false;
  unsigned int memory = 0;



  // change state to running
  processState = RUNNING;

  // todo

  while( !instructionsQueue.empty() )
  {

    // get the next instruction
    instruction = instructionsQueue.front();
    instructionsQueue.pop();

    // update parameters with the values stored in the instruction
    code = instruction.code;
    descriptor = instruction.descriptor;
    cycles = instruction.cycles;

    // get the time per cycle for the code-descriptor combination
    timePerCycle = getCycleTime(code, descriptor);

    // compute the total time to process the instruction
    runTime = cycles * timePerCycle * 1000;

    // log a message about this instruction
    logInstructionMessage(code, descriptor, stillRunning, memory);

    // process the instruction elsewhere
    memory = processsInstruction(code, descriptor, runTime);

    // log a final message about this instruction
    stillRunning = false;
    logInstructionMessage(code, descriptor, stillRunning, memory);

  }

}


/*
 * Get the desired cycle time for a device based on
 * the code and the descriptor provided
 */
int Process::getCycleTime(char code, string descriptor)
{
  int cycleTime = 0;

  // determine which cycle time to return, based on the code
  switch(code)
  {
    // case P
    case 'P':

      if( descriptor == "run" )
      {
        cycleTime = simulatorSettings.processorCycleTime;
      }
      break;

      // case I
    case 'I':

      if( descriptor == "hard drive" )
      {
        cycleTime = simulatorSettings.hardDriveCycleTime;
      }
      else if( descriptor == "monitor")
      {
        cycleTime = simulatorSettings.monitorDisplayTime;
      }
      else if( descriptor == "keyboard")
      {
        cycleTime = simulatorSettings.keyboardCycleTime;
      }
      break;

      // case O
    case 'O':

      if( descriptor == "hard drive" )
      {
        cycleTime = simulatorSettings.hardDriveCycleTime;
      }
      else if( descriptor == "monitor")
      {
        cycleTime = simulatorSettings.monitorDisplayTime;
      }
      else if( descriptor == "printer" )
      {
        cycleTime = simulatorSettings.printerCycleTime;
      }
      break;

      // case M
    case 'M':

      if( descriptor == "allocate" )
      {
        cycleTime = simulatorSettings.memoryCycleTime;
      }
      else if( descriptor == "cache")
      {
        cycleTime = simulatorSettings.memoryCycleTime;
      }
      break;
  }

  return cycleTime;
}


/*
 * todo
 */
void Process::logInstructionMessage(char code, string descriptor, bool stillRunning, unsigned int memory)
{
  logger->log("generic logging message");

  // todo
}


/*
 * Processes each instruction, which may include any of the following:
 *  - allocating memory, then waiting for a set time
 *  - creating a thread, which will wait for a set time
 *  - doing nothing, and then waiting for a set time
 */
unsigned int Process::processsInstruction(char code, string descriptor, int runTime)
{
  unsigned int memory = 0;
  timeval referenceTime;

  // todo - remove
  string time = "runTime: " + to_string(runTime) + "\n";
  printf(time.c_str());


  // get the time and store as a reference time
  gettimeofday( &referenceTime, NULL );

  // check if the code is 'M' and the descriptor 'allocate'
  if( code == 'M' && descriptor == "allocate")
  {
    // allocate memory
    memory = allocateMemory( simulatorSettings.systemMemory );
  }

  // if the code is I or O, spawn a thread to do the waiting operation
  if( code == 'I' || code == 'O')
  {

    logger->log("spawning a thread....");

    // spawn a thread
    pthread_create( &thread, NULL, threadRunner, (void*) &runTime );

    // wait for the thread to come back
    pthread_join(thread, NULL);

    logger->log("thread has been rejoined...");
  }

  // else, do the waiting operation here
  else
  {
    while( timePassed(referenceTime) < runTime );
  }

  // return
  return memory;
}














