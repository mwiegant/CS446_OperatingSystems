#include "Process.h"

Process::Process(SimCycleTimes cycleTimes, Logger* logger, queue<Instruction> instructionsQueue )
{
  this->cycleTimes = cycleTimes;
  this->logger = logger;
  this->instructionsQueue = instructionsQueue;

  logger->log("successfully created a new process!!!");
}


Process::~Process()
{

}