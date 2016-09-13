#include <iostream>

#include "Simulation.h"
#include "Metadata.h"
#include "Processor.h"

using namespace std;


int main(int argc, char **argv)
{
  Simulation *simulation = new Simulation();
  Metadata *metadata = new Metadata();
//  Processor *processor = new Processor();

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

  // setup the Processor object and start reading in the metadata file
  if( !metadata->readInMetadata( metadataFilePath ) )
  {
    cout << "Error - Failed to read in the metadata file at: " << metadataFilePath << endl;
    return -2;
  }

  // todo - run the simulation



  return 0;
}