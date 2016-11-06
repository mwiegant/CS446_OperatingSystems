#include "ResourceManager.h"

ResourceManager::ResourceManager(int uniqueResourceTypes)
{
  numResourceTypes = uniqueResourceTypes;

  initialized = false;
}

ResourceManager::~ResourceManager()
{

}

bool ResourceManager::Initialize(int monitorQuantity, int hddQuantity, int printerQuantity, int keyboardQuantity)
{
  // initialize semaphores and maximum resource amounts
  semaphores = new int[numResourceTypes];
  maximumResources = new int[numResourceTypes];

  semaphores[MONITOR] = monitorQuantity;
  semaphores[HDD] = hddQuantity;
  semaphores[PRINTER] = printerQuantity;
  semaphores[KEYBOARD] = keyboardQuantity;

  maximumResources[MONITOR] = monitorQuantity;
  maximumResources[HDD] = hddQuantity;
  maximumResources[PRINTER] = printerQuantity;
  maximumResources[KEYBOARD] = keyboardQuantity;

  // initialize mutexes
  mutexes = new bool*[numResourceTypes];

  // initialize the arrays of pointers that mutexes point to
  mutexes[MONITOR] = new bool[monitorQuantity];
  mutexes[HDD] = new bool[hddQuantity];
  mutexes[PRINTER] = new bool[printerQuantity];
  mutexes[KEYBOARD] = new bool[keyboardQuantity];

  // set default values of true to every mutex flag
  for(int i = 0; i < monitorQuantity; i++)
  {
    mutexes[MONITOR][i] = true;
  }

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