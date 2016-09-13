#ifndef OPERATING_SYSTEM_METADATA_H
#define OPERATING_SYSTEM_METADATA_H

#include <list>
#include <vector>
#include <string>
#include <cstring>
#include <fstream>
#include <iostream>

using namespace std;

class Metadata
{
  public:
    Metadata();
    ~Metadata();
    bool readInMetadata(string filePath);

private:
  // for parsing components of the metadata file
  void extractMetadataFromLine(string fileData);
  void addMetadata(string metadata);

  // additional helper functions for parsing
  void splitString(string theString, char delimiter, vector<string> &theSplitString);
  void splitString(string theString, char delimiter1, char delimiter2, vector<string> &theSplitString);
  void removeExtraWhitespace(string &str);

  // struct for holding metadata commands
  struct Instruction
  {
      char code;
      string descriptor;
      int cycles;
  };

  // for holding all the metadata commands
  list<Instruction> instructions;
  list<Instruction>::iterator instruction;

};

#endif //OPERATING_SYSTEM_METADATA_H
