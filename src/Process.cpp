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

/*
 * Constructor
 */
Process::Process(int processId, SimulatorSettings simulatorSettings, Logger* logger, queue<Instruction> instructionsQueue )
{
  this->processId = processId;
  this->simulatorSettings = simulatorSettings;
  this->logger = logger;
  this->instructionsQueue = instructionsQueue;

  // set default state to ready
  processState = READY;
}


Process::~Process()
{

}


/*
 * Cycles through all instructions in this process
 */
void Process::Run( timeval startTime )
{
  char code;
  string descriptor;
  Instruction instruction;
  bool stillRunning;
  int cycles, timePerCycle, runTime;
  unsigned int memory = 0;

  // assign the start time
  referenceTime = startTime;

  // change state to running
  processState = RUNNING;

  while( !instructionsQueue.empty() )
  {

    // set running flag
    stillRunning = true;

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

  // assume if all instructions have been read that this process is terminating
  processState = TERMINATED;

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
 * Log messages to the logger, according to:
 *  - the type of instruction, and
 *  - whether the instruction is about to run or just finished running
 */
void Process::logInstructionMessage(char code, string descriptor, bool stillRunning, unsigned int memory)
{
  string message;
  bool badInstruction = false;

  // get the timestamp
  message = timeToString( timePassed(referenceTime) ) + " - ";


  // determine which message to log,
  // based first on the code/descripter, and second on if it's running still or not
  switch(code)
  {
    // case A
    case 'A':

      if( descriptor == "start")
      {
        if(stillRunning)  message += "OS: preparing process " + to_string(processId);
        else              message += "OS: starting process " + to_string(processId);
      }
      else if( descriptor == "end")
      {
        if(stillRunning)  message += "OS: removing process " + to_string(processId);
        else              message = "";
      }
      else
      {
        badInstruction = true;
      }
      break;

    // case I
    case 'I':

      if( descriptor == "hard drive" )
      {
        if(stillRunning)  message += "Process " + to_string(processId) + ": start hard drive input";
        else              message += "Process " + to_string(processId) + ": end hard drive input";
      }
      // todo - is there an input monitor command???
      else if( descriptor == "monitor")
      {
        if(stillRunning)  message += "Process " + to_string(processId) + ": start monitor input";
        else              message += "Process " + to_string(processId) + ": end monitor input";
      }
      else if( descriptor == "keyboard")
      {
        if(stillRunning)  message += "Process " + to_string(processId) + ": start keyboard input";
        else              message += "Process " + to_string(processId) + ": end keyboard input";
      }
      else
      {
        badInstruction = true;
      }
      break;

    // case O
    case 'O':

      if( descriptor == "hard drive" )
      {
        if(stillRunning)  message += "Process " + to_string(processId) + ": start hard drive output";
        else              message += "Process " + to_string(processId) + ": end hard drive output";
      }
      else if( descriptor == "monitor")
      {
        if(stillRunning)  message += "Process " + to_string(processId) + ": start monitor output";
        else              message += "Process " + to_string(processId) + ": end monitor output";
      }
      else if( descriptor == "printer" )
      {
        if(stillRunning)  message += "Process " + to_string(processId) + ": start printer output";
        else              message += "Process " + to_string(processId) + ": end printer output";
      }
      else
      {
        badInstruction = true;
      }
      break;

    // case P
    case 'P':

      if( descriptor == "run" )
      {
        if(stillRunning)  message += "Process " + to_string(processId) + ": start processing action";
        else              message += "Process " + to_string(processId) + ": end processing action";
      }
      else
      {
        badInstruction = true;
      }
      break;

    // case M
    case 'M':

      if( descriptor == "allocate" )
      {
        if(stillRunning)  message += "Process " + to_string(processId) + ": allocating memory";
        else              message += "Process " + to_string(processId) + ": memory allocated at " + memoryToString(memory);
      }
      else if( descriptor == "cache")
      {
        if(stillRunning)  message += "Process " + to_string(processId) + ": start memory caching";
        else              message += "Process " + to_string(processId) + ": end memory caching";
      }
      else
      {
        badInstruction = true;
      }
      break;

    // case S
    case 'S':

      if( descriptor == "start" )
      {
        if(stillRunning)  message += "Simulator program starting";
        else              message = "";
      }
      else if( descriptor == "end")
      {
        if(stillRunning)  message += "Simulator program ending";
        else              message = "";
      }
      else
      {
        badInstruction = true;
      }
      break;
  }

  // check for bad instruction
  if( badInstruction )
  {
    message = "Error - unrecognized instruction, with code '";
    message += to_string(code) + "', and descriptor '" + descriptor + "'.";
  }

  // log the message, if there is a message to log
  if( strlen(message.c_str()) > 0 )
  {
    logger->log(message);
  }
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
    // spawn a thread
    pthread_create( &thread, NULL, threadRunner, (void*) &runTime );

    // wait for the thread to come back
    pthread_join(thread, NULL);
  }

  // else, do the waiting operation here
  else
  {
    while( timePassed(referenceTime) < runTime );
  }

  // return
  return memory;
}


/*
 * Asthetic function for nice-looking timestamps
 *
 * Converts a time passed from a raw number into a floating number representation
 *
 *   i.e., something like that: 0.123400  (where the time was 123400)
 */
string Process::timeToString(int time)
{
  // get the number components
  int sec = time / 1000000;
  int remainder = time % 1000000;

  string stringRemainder = to_string(remainder);

  // make the remainder larger so it has the right number of digits
  // (example: 122 -> 000123)
  while( strlen( stringRemainder.c_str() ) < 6 )
  {
    stringRemainder = "0" + stringRemainder;
  }

  // combine them together into a string
  string result = to_string(sec) + "." + stringRemainder;

  return result;
}


/*
 * Asthetic function for nice-looking memory addressing.
 *
 * Converts a number from the total memory of the simulator to a hex address.
 *
 *  i.e., something like this: 0x0012345  (where there is total memory of 1000000)
 */
string Process::memoryToString(int _memoryAddress)
{
  // turn number values into strings
  string totalMemory = to_string( simulatorSettings.systemMemory );
  string memoryAddress = to_string( _memoryAddress );

  // determine how many zeros I'll need (ex: the '00' in 0x0012345)
  int zeros = strlen(totalMemory.c_str()) - strlen(memoryAddress.c_str());

  string result = "0x";

  // add zeros to the result string
  for( zeros; zeros > 0; zeros--)
  {
    result += "0";
  }

  // finally, add the memory address to the result string
  result += memoryAddress;

  return result;
}









