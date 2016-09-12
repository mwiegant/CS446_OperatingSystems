#include <iostream>

#include "Simulation.h"

using namespace std;

// todo - handle user not passing in a filename
// todo - implement Simulation object

int main(int argc, char **argv)
{
  Simulation *simulation = new Simulation();
  string metadataFilePath;


  // check if the user provided enough arguments
  if( argc != 2 )
  {
    cout << "Error - Must provide a filename for the simulator configuration." << endl;
    return -1;
  }

  // prove that I can interact with the Simulation object
  simulation->showSimulationSettings();


  // setup the Simulation object and start reading in the config file
  // todo


  return 0;
}