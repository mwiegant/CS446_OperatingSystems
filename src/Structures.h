#ifndef OPERATING_SYSTEM_STRUCTURES_H
#define OPERATING_SYSTEM_STRUCTURES_H

#include <string>

// structure for holding metadata instructions
struct Instruction
{
  char code;
  std::string descriptor;
  int cycles;
};

struct SimCycleTimes
{
  int processorCycleTime;
  int monitorDisplayTime;
  int hardDriveCycleTime;
  int printerCycleTime;
  int keyboardCycleTime;
  int memoryCycleTime;
};

// todo - add structure(s) for Simulation properties


#endif //OPERATING_SYSTEM_STRUCTURES_H
