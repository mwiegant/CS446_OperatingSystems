#include "Processor.h"

Processor::Processor()
{

}

Processor::~Processor()
{

}

void Processor::setLogger(Logger *theLogger)
{
  logger = theLogger;
}

void Processor::processInstructions(Simulation simulation, Metadata *metadata)
{
  // fields for the metadata
  string descriptor;
  string message;
  char code;
  int cycles;
  int timePerCycle;
  int totalTime;

  // log metadata metrics
  logger->log("Meta-Data Metrics");

  // log metadata instructions while there are instructions to log
  while( metadata->fetchNextInstruction(code, descriptor, cycles) )
  {

    // get the time per cycle for the code-descriptor combination
    timePerCycle = simulation.getCycleTime(code, descriptor);

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

