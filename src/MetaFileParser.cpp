#include "MetaFileParser.h"

MetaFileParser::MetaFileParser()
{

}

MetaFileParser::~MetaFileParser()
{

}


/*
 *  Read in the entire metadata file. Since each line from the file contains
 *  multiple meta data instructions, and they may be separated by different
 *  delimiters, each line is sent to a function to break a line up into individual
 *  instructions, and then a final function stores the instruction inside
 *  an object that can easily be manipulated at a later time.
 */
bool MetaFileParser::readInMetadata(char filePath[], queue<Instruction> &instructions)
{
  ifstream fin;
  string linedata;
  bool readFile = false;
  bool firstLine = true;

  // clear input file-stream flags and open the file
  fin.clear();
  fin.open(filePath);

  while( fin.good() )
  {
    readFile = true;

    // get one line at a time
    getline(fin, linedata, '\n');

    // don't try to extract data from the first line
    if(firstLine)
    {
      firstLine = false;
    }

    else
    {
      // send the line of instructions to be broken up elsewhere
      extractInstructionsFromLine(linedata);
    }
  }

  fin.close();

  // check if the queue of instructions was filled
  if( this->instructions.empty() )
  {
    printf("Error - failed to load any metadata instructions from metadata file at %s.\n", filePath);
    return false;
  }

  // if the queue has instructions in it, copy them into the reference queue
  else
  {
    // keep emptying out the internal queue until it is empty
    while( !this->instructions.empty() )
    {
      instructions.push( this->instructions.front() );
      this->instructions.pop();
    }
  }

  return readFile;
}


/*
 * Takes an entire line of metadata instructions and splits up the line
 * into separate metadata instructions. The separate metadata instructions
 * are sent from here to a final function to be processed into an Instruction object
 */
void MetaFileParser::extractInstructionsFromLine(string fileData)
{
  vector<string> metaDatas;

  // split up the meta data into separate metadata tokens, split up by whitespaces
  splitString(fileData, ';', ':', metaDatas);

  // only proceed if there was more than one token parsed from the line
  if( metaDatas.size() > 1 ) {

    // for each meta data token
    for( int i = 0; i < metaDatas.size(); i++ )
    {

      // process this meta data token, if it appears to be a valid metadata instruction
      if( strlen(metaDatas[i].c_str()) > 5 )
      {
        makeInstruction(metaDatas[i]);
      }
    }
  }
}


/*
 * Takes in a single metadata instruction and parses it into an instruction object that can be
 * added to the set of instructions to eventually run
 */
void MetaFileParser::makeInstruction(string metadata)
{
  vector<string> tokens;
  Instruction newInstruction;

  // trim whitespace from the metadata string
  removeExtraWhitespace(metadata);

  // split metadata into separate tokens, split up by ( and )
  splitString(metadata, '(', ')', tokens);

  // add fields to a new metadata struct object
  // tokens[0][0] gets the first character from a string that is 1 character long (this is not a bug)
  newInstruction.code = tokens[0][0];
  newInstruction.descriptor = tokens[1];
  newInstruction.cycles = stoi(tokens[2]);

  // push this new metadata into the internal list of instructions
  instructions.push(newInstruction);

}




























