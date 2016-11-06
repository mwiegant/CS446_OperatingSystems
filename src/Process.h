#ifndef OPERATING_SYSTEM_PROCESS_H
#define OPERATING_SYSTEM_PROCESS_H

/*
 * CLASS - Process
 *
 * ABOUT - Class for running processes. Each process represents a
 *  subset of the entire queue of metadata instructions. The process
 *  performs all operations needed to process meta instructions
 *  including threading, memory allocation, and pausing for time.
 */

#include <cstdlib>
#include <time.h>
#include <sys/time.h>
#include <queue>
#include <cstring>
#include <string>
#include <pthread.h>

#include "Structures.h"
#include "Logger.h"
#include "ResourceManager.h"

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
    Process(int processId, SimulatorSettings simulatorSettings, Logger* logger, ResourceManager* resourceManager,
            queue<Instruction> instructionsQueue );
    ~Process();

    void Run( timeval startTime );

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

    // process id number
    int pid;

    // the state of this process
    ProcessControlBlock processState;

    // Processing Times
    SimulatorSettings simulatorSettings;

    // Logging Object
    Logger* logger;

    // Resource Manager Object
    ResourceManager* resourceManager;

    // Queue for holding instructions
    queue<Instruction> instructionsQueue;
};


#endif //OPERATING_SYSTEM_PROCESS_H
