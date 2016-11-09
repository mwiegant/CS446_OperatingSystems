#define NULL 0

#include <iostream>

#include "Simulation.h"

using namespace std;


int main(int argc, char **argv)
{
  Simulation *simulation = new Simulation();

  // check if the user provided a config file path
  if( argc < 2 )
  {
    cout << "Error - Must provide a filename for the simulator configuration." << endl;
    return -1;
  }

  cout << "about to call simulation initialize" << endl;

  // initialize the simulation
  if( !simulation->Initialize(argv[1]) )
  {
    cout << "Error - Failed to initialize the simulation." << endl;
    return -2;
  }

  cout << "got past simulation initialize" << endl;

  // process metadata instructions
  simulation->Run();

  // de-allocate simulation
  delete simulation;
  simulation = NULL;

  return 0;
}