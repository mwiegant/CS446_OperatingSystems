#ifndef OPERATING_SYSTEM_STRUCTURES_H
#define OPERATING_SYSTEM_STRUCTURES_H

/*
 * ABOUT - Header file that contains structures needed by
 *  certain class objects in this codebase. Any class object
 *  that needs one of these structures should include this
 *  file.
 */

#include <string>

// structure for holding metadata instructions
struct Instruction
{
  char code;
  std::string descriptor;
  int cycles;
};

// structure for holding simulation cycle times
struct SimulatorSettings
{
  int systemMemory;
  int processorCycleTime;
  int monitorDisplayTime;
  int hardDriveCycleTime;
  int printerCycleTime;
  int keyboardCycleTime;
  int memoryCycleTime;
};

// enumeration for a Process Control Block
enum ProcessControlBlock
{
  NEW,
  READY,
  RUNNING,
  WAITING,
  TERMINATED
};




#endif //OPERATING_SYSTEM_STRUCTURES_H
