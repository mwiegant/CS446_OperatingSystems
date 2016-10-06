#ifndef OPERATING_SYSTEM_PROCESS_H
#define OPERATING_SYSTEM_PROCESS_H

#include <queue>
#include <string>

#include "Structures.h"
#include "Logger.h"

using namespace std;

class Process
{
  public:
    Process(SimCycleTimes cycleTimes, Logger* logger, queue<Instruction> instructionsQueue );
    ~Process();

  private:

    // Processing Times
    SimCycleTimes cycleTimes;

    // Logging Object
    Logger *logger;

    // Queue for holding instructions
    queue<Instruction> instructionsQueue;
};


#endif //OPERATING_SYSTEM_PROCESS_H
