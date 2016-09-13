#include <iostream>

#include "Simulation.h"

using namespace std;


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

  // setup the Simulation object and start reading in the config file
  if( !simulation->readInConfig(argv[1]) )
  {
    cout << "Error - Failed to read in the config file at: " << argv[1] << endl;
    return -2;
  }

  // prove that I can get data stored into the Simulation object
  simulation->showSimulationSettings();

  // get the metadata file from the simulation
  metadataFilePath = simulation->getMetadataFilePath();


  // todo - get stuff to the processor class


  return 0;
}