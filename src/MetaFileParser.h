#ifndef OPERATING_SYSTEM_METADATAPARSER_H
#define OPERATING_SYSTEM_METADATAPARSER_H

#include <queue>
#include <cstdio>

#include "Structures.h"

#include "FileParser.h"

using namespace std;


class MetaFileParser : public FileParser
{
  public:
    MetaFileParser();
    ~MetaFileParser();

    bool readInMetadata(char filePath[], queue<Instruction> &instructions);

  private:
    // for parsing components of the metadata file
    void extractInstructionsFromLine(string fileData);
    void makeInstruction(string metadata);

    // Queue for holding instructions
    queue<Instruction> instructions;
};

#endif //OPERATING_SYSTEM_METADATAPARSER_H