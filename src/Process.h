#ifndef OPERATING_SYSTEM_PROCESS_H
#define OPERATING_SYSTEM_PROCESS_H

#include <cstdlib>
#include <time.h>
#include <sys/time.h>
#include <queue>
#include <cstring>
#include <string>
#include <pthread.h>

// todo - remove when done testing
#include <cstdio>

#include "Structures.h"
#include "Logger.h"

using namespace std;

/*
 * ===============================================================================
 * ========================>  HELPER FUNCTIONS  <========================
 * ===============================================================================
 */

// for use in waiting for a set time
int timePassed( struct timeval referenceTime );

// used for memory allocation instructions
unsigned int allocateMemory( int totalMemory );

// the function that threads will run
void* threadRunner(void* _waitTime);

/*
 * ===============================================================================
 * ========================>  CLASS DECLARATION  <========================
 * ===============================================================================
 */

class Process
{
  public:
    Process(SimulatorSettings simulatorSettings, Logger* logger, queue<Instruction> instructionsQueue );
    ~Process();

    void Run( int processNumber, timeval startTime );

  private:

    int getCycleTime(char code, string descriptor);

    void logInstructionMessage(char code, string descriptor, bool stillRunning, unsigned int memory);

    unsigned int processsInstruction(char code, string descriptor, int runTime);

    // logging helper functions
    string timeToString(int time);
    string memoryToString(int _memoryAddress);

    // for use with logging
    int processId;
    timeval referenceTime;

    // thread object
    pthread_t thread;

    // the state of this process
    ProcessControlBlock processState;

    // Processing Times
    SimulatorSettings simulatorSettings;

    // Logging Object
    Logger *logger;

    // Queue for holding instructions
    queue<Instruction> instructionsQueue;
};


#endif //OPERATING_SYSTEM_PROCESS_H
