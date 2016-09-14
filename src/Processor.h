#ifndef OPERATING_SYSTEM_PROCESSOR_H
#define OPERATING_SYSTEM_PROCESSOR_H

#include "Simulation.h"
#include "Metadata.h"
#include "Logger.h"


using namespace std;

class Processor
{
  public:
    Processor();
    ~Processor();
    void setLogger(Logger *theLogger);

    void processInstructions(const Simulation simulation, Metadata metadata);

  private:
    Logger *logger;

};



#endif //OPERATING_SYSTEM_PROCESSOR_H
