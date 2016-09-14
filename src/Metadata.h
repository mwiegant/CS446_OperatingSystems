#ifndef OPERATING_SYSTEM_METADATA_H
#define OPERATING_SYSTEM_METADATA_H

// todo - remove iostream after I am confident Processor is processing instructions
#include <iostream>

#include <queue>
#include <vector>
#include <string>
#include <cstring>
#include <fstream>

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
  queue<Instruction> instructions;

};

#endif //OPERATING_SYSTEM_METADATA_H
