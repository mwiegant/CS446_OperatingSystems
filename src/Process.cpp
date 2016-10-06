#include "Process.h"

Process::Process(SimCycleTimes cycleTimes, Logger* logger, queue<Instruction> instructionsQueue )
{
  this->cycleTimes = cycleTimes;
  this->logger = logger;
  this->instructionsQueue = instructionsQueue;

  // set default state to new
  processState = NEW;

  logger->log("successfully created a new process!!!");
}


Process::~Process()
{

}


/*
 * Cycles through all instructions in this process
 */
void Process::Run()
{
  // todo
}



/*
 * Meant to be used by threads.
 *
 * Takes in a wait time, and doesn't exit from the thread
 * until the wait time has expired.
 */
void* Process::threadRunner(void* waitTime)
{

  // todo

  pthread_exit(0);
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
        cycleTime = cycleTimes.processorCycleTime;
      }
      break;

      // case I
    case 'I':

      if( descriptor == "hard drive" )
      {
        cycleTime = cycleTimes.hardDriveCycleTime;
      }
      else if( descriptor == "monitor")
      {
        cycleTime = cycleTimes.monitorDisplayTime;
      }
      else if( descriptor == "keyboard")
      {
        cycleTime = cycleTimes.keyboardCycleTime;
      }
      break;

      // case O
    case 'O':

      if( descriptor == "hard drive" )
      {
        cycleTime = cycleTimes.hardDriveCycleTime;
      }
      else if( descriptor == "monitor")
      {
        cycleTime = cycleTimes.monitorDisplayTime;
      }
      else if( descriptor == "printer" )
      {
        cycleTime = cycleTimes.printerCycleTime;
      }
      break;

      // case M
    case 'M':

      if( descriptor == "allocate" )
      {
        cycleTime = cycleTimes.memoryCycleTime;
      }
      else if( descriptor == "cache")
      {
        cycleTime = cycleTimes.memoryCycleTime;
      }
      break;
  }

  return cycleTime;
}