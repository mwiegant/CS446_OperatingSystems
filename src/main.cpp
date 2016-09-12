#include <iostream>

using namespace std;

// todo - handle user not passing in a filename
// todo - implement Simulation object

int main(int argc, char **argv)
{
  // check if the user provided enough arguments
  if( argc != 2 )
  {
    cout << "Error - Must provide a filename for the simulator configuration." << endl;
    return -1;
  }

  cout << "#DEBUG - provided filename: " << argv[1] << endl;


  return 0;
}