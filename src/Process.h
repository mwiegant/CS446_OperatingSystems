#ifndef OPERATING_SYSTEM_PROCESS_H
#define OPERATING_SYSTEM_PROCESS_H

#include <queue>
#include <string>
#include <pthread.h>


#include "Structures.h"
#include "Logger.h"

using namespace std;

class Process
{
  public:
    Process(SimCycleTimes cycleTimes, Logger* logger, queue<Instruction> instructionsQueue );
    ~Process();

    void Run();

  private:

    // the function that threads will run
    void* threadRunner(void* waitTime);

    int getCycleTime(char code, string descriptor);

    // the state of this process
    ProcessControlBlock processState;

    // Processing Times
    SimCycleTimes cycleTimes;

    // Logging Object
    Logger *logger;

    // Queue for holding instructions
    queue<Instruction> instructionsQueue;
};


#endif //OPERATING_SYSTEM_PROCESS_H
