#include "ResourceManager.h"

ResourceManager::ResourceManager(int uniqueResourceTypes)
{
  numResourceTypes = uniqueResourceTypes;

  initialized = false;
}

ResourceManager::~ResourceManager()
{

}

bool ResourceManager::Initialize(int hddQuantity, int printerQuantity, int keyboardQuantity,
                                 int totalMemory, int memoryBlockSize)
{

  // initialize quantified resources
  if( !InitializeQuantities( hddQuantity, printerQuantity, keyboardQuantity ) )
  {
    return false;
  }

  // initialize memory resources
  if( !InitializeMemory( totalMemory, memoryBlockSize ) )
  {
    return false;
  }

  return true;
}


/*
 * Given the type of the resource to request, returns the first free resource
 * of that type, if any are available. If no resources of that type are
 * available, this function returns false
 */
bool ResourceManager::RequestResource(int resourceType, int& resourceIndex)
{
  // error checking
  if( resourceType >= numResourceTypes )
  {
    printf("Error - tried to request invalid resource type from the resource manager.\n");
    return false;
  }

  if( !initialized )
  {
    printf("Error - tried to request resources before resource manager was initialized.\n");
    return false;
  }

  // check if there are no resources available of the desired type
  if( semaphores[resourceType] <= 0 )
  {
    return false;
  }

  // else, fetch the next available resource of the desired type
  for( resourceIndex = 0; resourceIndex < maximumResources[resourceType]; resourceIndex++ )
  {
    if( mutexes[resourceType][resourceIndex] == true )
    {
      mutexes[resourceType][resourceIndex] = false;
      semaphores[resourceType]--;
      break;
    }
  }

  return true;
}


/*
 * Takes in a resource type and the index of a resource. Updates the semaphore
 * count and the appropriate mutex flag to indicate the resource is available
 * for use again
 */
bool ResourceManager::FreeResource(int resourceType, int resourceIndex)
{
  // error checking
  if( resourceType >= numResourceTypes )
  {
    printf("Error - tried to request invalid resource type from the resource manager.\n");
    return false;
  }

  if( resourceIndex >= maximumResources[resourceType] || mutexes[resourceType][resourceIndex] != false)
  {
    printf("Error - tried to free up a resource that either doesn't exist or which wasn't in use.\n");
    return false;
  }

  // increment the semaphore count and update the appropriate mutex
  semaphores[resourceType]++;
  mutexes[resourceType][resourceIndex] = true;

  return true;
}


/*
 * Looks through memory for the next available memory location from whichever block
 * of memory is currently being cycled through.
 */
bool ResourceManager::RequestMemory(unsigned int& theMemoryLocation)
{
  bool acquiredUnusedMemory = false;
  bool memoryIsInUse = false;
  int memoryAddress = memoryBlockSize * currentMemoryBlock;

  // error checking
  if( !initialized )
  {
    printf("Error - tried to request memory access before resource manager was initialized.\n");
    return false;
  }

  // keep trying to acquire a new, unused memory until one is found
  do
  {
    // reset flags
    memoryIsInUse = false;

    // check if the memory address is already in-use
    for( int i = 0; i < inUseMemory.size(); i++ )
    {
      if( inUseMemory[i] == memoryAddress )
      {
        memoryIsInUse = true;
      }
    }

    // if the memory address is in-use, generate a new one
    if( memoryIsInUse )
    {
      memoryAddress++;
      continue;
    }

    // else, store this memory address and move to the next block for next time
    inUseMemory.push_back(memoryAddress);
    theMemoryLocation = memoryAddress;
    acquiredUnusedMemory = true;
    currentMemoryBlock++;

    // reset the current memory block if it is now out of range
    if( currentMemoryBlock >= totalMemoryBlocks )
    {
      currentMemoryBlock = 0;
    }

  } while( acquiredUnusedMemory == false );

  return true;
}


/*
 * Attempts to return the given memory location back to available memory
 * by removing it from the list of known in-use memory locations.
 */
bool ResourceManager::FreeMemory(unsigned int& theMemoryLocation)
{
  int index = -1;

  // error checking
  if( inUseMemory.size() == 0 )
  {
    printf("Error - tried to free memory when none was in use.\n");
    return false;
  }

  // find the index of the memory location
  for( int i = 0; i < inUseMemory.size(); i++ )
  {
    if( inUseMemory[i] == theMemoryLocation)
    {
      index = i;
      break;
    }
  }

  // error checking - element not found
  if( index == -1 )
  {
    printf("Error - could not find the specified memory location in in-use memory.\n");
    return false;
  }

  // remove the element specified by the memory location
  inUseMemory.erase( inUseMemory.begin() + index );

  return true;
}


/*
 * Handles set up of semaphores and mutexes for quantified resources such as hard drives
 * or printers.
 */
bool ResourceManager::InitializeQuantities(int hddQuantity, int printerQuantity, int keyboardQuantity)
{
  // initialize semaphores and maximum resource amounts
  semaphores = new int[numResourceTypes];
  maximumResources = new int[numResourceTypes];

  semaphores[HDD] = hddQuantity;
  semaphores[PRINTER] = printerQuantity;
  semaphores[KEYBOARD] = keyboardQuantity;

  maximumResources[HDD] = hddQuantity;
  maximumResources[PRINTER] = printerQuantity;
  maximumResources[KEYBOARD] = keyboardQuantity;

  // initialize mutexes
  mutexes = new bool*[numResourceTypes];

  // initialize the arrays of pointers that mutexes point to
  mutexes[HDD] = new bool[hddQuantity];
  mutexes[PRINTER] = new bool[printerQuantity];
  mutexes[KEYBOARD] = new bool[keyboardQuantity];

  // set default values of true to every mutex flag
  for(int i = 0; i < hddQuantity; i++)
  {
    mutexes[HDD][i] = true;
  }

  for(int i = 0; i < printerQuantity; i++)
  {
    mutexes[PRINTER][i] = true;
  }

  for(int i = 0; i < keyboardQuantity; i++)
  {
    mutexes[KEYBOARD][i] = true;
  }

  initialized = true;

  return true;
}


/*
 * Handles the set up of memory resources, including setting up structures that
 * will be used to provide access to memory or keep track of which memory
 * addresses are already in use.
 */
bool ResourceManager::InitializeMemory(int _totalMemory, int _memoryBlockSize)
{
  // initialize memory management variables
  totalMemory = _totalMemory;
  memoryBlockSize = _memoryBlockSize;

  currentMemoryBlock = 0;

  // calculate the total number of blocks of memory
  totalMemoryBlocks = totalMemory / memoryBlockSize;

  if( totalMemory % memoryBlockSize != 0 )
  {
    totalMemoryBlocks++;
  }

  return true;
}




