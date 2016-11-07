#ifndef OPERATING_SYSTEM_RESOURCEMANAGER_H
#define OPERATING_SYSTEM_RESOURCEMANAGER_H

/*
 * Manages the use of resources in the simulation, keeping track
 * of which resources are in use as well as how many are still
 * available to be used.
 *
 * Processes must request resources from this manager. Resources
 * will always be distributed so long as there are any remaining
 * to be distributed.
 */

#include <cstdio>

#include "Structures.h"

using namespace std;

class ResourceManager
{
  public:
    ResourceManager(int uniqueResourceTypes);
    ~ResourceManager();

    bool Initialize(int hddQuantity, int printerQuantity, int keyboardQuantity);

    bool RequestResource(int resourceType, int& resourceIndex);
    bool FreeResource(int resourceType, int resourceIndex);

  private:

    // flag to ensure initialize was called
    bool initialized;

    // the number of unique types of resources
    int numResourceTypes;

    // resource management devices
    int* maximumResources;
    int* semaphores;
    bool** mutexes;

};


#endif //OPERATING_SYSTEM_RESOURCEMANAGER_H