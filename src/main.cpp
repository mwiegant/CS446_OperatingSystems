#include <iostream>

#include "Simulation.h"
#include "Metadata.h"

using namespace std;


int main(int argc, char **argv)
{
  Simulation *simulation = new Simulation();
  Metadata *metadata = new Metadata();
  string metadataFilePath;


  // check if the user provided a config file path
  if( argc < 2 )
  {
    cout << "Error - Must provide a filename for the simulator configuration." << endl;
    return -1;
  }


  // initialize the simulation
  if( !simulation->Initialize(argv[1]) )
  {
    cout << "Error - Failed to initialize the simulation." << endl;
    return -2;
  }

  // get the metadata file from the simulation
  metadataFilePath = simulation->getMetadataFilePath();

  // read in the metadata file
  if( !metadata->readInMetadata( metadataFilePath ) )
  {
    cout << "Error - Failed to read in the metadata file at: " << metadataFilePath << endl;
    return -2;
  }

  // process metadata instructions
  simulation->Run(metadata);


  return 0;
}