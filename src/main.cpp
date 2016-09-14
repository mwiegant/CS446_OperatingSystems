#include <iostream>

#include "Simulation.h"
#include "Metadata.h"
#include "Logger.h"
#include "Processor.h"

using namespace std;


int main(int argc, char **argv)
{
  Simulation *simulation = new Simulation();
  Metadata *metadata = new Metadata();
  Processor *processor = new Processor();
  Logger *logger = new Logger();
  string metadataFilePath;


  // check if the user provided a config file path
  if( argc < 2 )
  {
    cout << "Error - Must provide a filename for the simulator configuration." << endl;
    return -1;
  }

  // setup logger for simulation
  simulation->setLogger(logger);

  // read in the config file
  if( !simulation->readInConfig(argv[1]) )
  {
    cout << "Error - Failed to read in the config file at: " << argv[1] << endl;
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

  // setup logger for processor
  processor->setLogger(logger);

  // process metadata instructions
//  processor->processInstructions(simulation, metadata);


  return 0;
}