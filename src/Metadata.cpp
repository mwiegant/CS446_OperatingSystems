#include "Metadata.h"

Metadata::Metadata()
{

}

Metadata::~Metadata()
{

}

/*
 *  Read in the entire metadata file.
 */
bool Metadata::readInMetadata(string filePath)
{
  ifstream fin;
  string linedata;
  bool readFile = false;
  bool firstLine = true;

  // clear input file-stream flags and open the file
  fin.clear();
  fin.open(filePath.c_str());

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


      // send the line to data extraction function
      extractMetadataFromLine(linedata);
    }

  }

  fin.close();

  return readFile;
}


void Metadata::splitString(string theString, char delimiter, vector<string> &theSplitString)
{
  string tempString;
  int stringLength = strlen(theString.c_str());

  // iterate over the length of theString
  for(int i = 0; i < stringLength; i++) {

    // check if char in string is the delimiter
    if( theString[i] == delimiter ) {

      // push tempString to theSplitString
      theSplitString.push_back(tempString);

      // reset tempString
      tempString = "";

    }
    else
    {
      // add char to tempString
      tempString += theString[i];
    }
  }

  // push the final portion of the tempString to theSplitString
  theSplitString.push_back(tempString);
}


void Metadata::splitString(string theString, char delimiter1, char delimiter2, vector<string> &theSplitString)
{
  string tempString;
  int stringLength = strlen(theString.c_str());

  // iterate over the length of theString
  for(int i = 0; i < stringLength; i++) {

    // check if char in string is the delimiter
    if( theString[i] == delimiter1 ||  theString[i] == delimiter2) {

      // push tempString to theSplitString
      theSplitString.push_back(tempString);

      // reset tempString
      tempString = "";

    }
    else
    {
      // add char to tempString
      tempString += theString[i];
    }
  }

  // push the final portion of the tempString to theSplitString
  theSplitString.push_back(tempString);
}


/*
 * Removes leading and trailing whitespace by copying the passed in string
 * into a new string that doesn't have those whitespaces and overriding the
 * original string.
 */
void Metadata::removeExtraWhitespace(string &str)
{
  int strLength = strlen(str.c_str());
  string tempStr = "";

  // copy the first character of str into the new string if the first character isn't whitespace
  if( str[0] != ' ' )
  {
    tempStr += str[0];
  }

  // copy the remaining characters of str into the new string, except for the very last character
  for( int index = 1; index < strLength - 1; index++ )
  {
    tempStr += str[index];
  }

  // copy the last character of str into the new string if the last character isn't whitespace
  if( (strLength > 0) && (str[strLength - 1] != ' ') )
  {
    tempStr += str[strLength - 1];
  }

  // override str with tempStr
  str = tempStr;
}


/*
 * Takes a line from the metadata file and splits it up into separate metadata instructions
 */
void Metadata::extractMetadataFromLine(string fileData)
{
  vector<string> metaDatas;

  // split up the meta data into separate tokens, split up by whitespaces
  splitString(fileData, ';', ':', metaDatas);

  // only proceed if there was more than one token parsed from the line
  if( metaDatas.size() > 1 ) {

    // for each meta data token
    for( int i = 0; i < metaDatas.size(); i++ )
    {

      // add meta data token to the list of instructions, if it appears to be a valid instruction
      if( strlen(metaDatas[i].c_str()) > 5 )
      {
        addMetadata(metaDatas[i]);
      }
    }
  }
}


/*
 * Takes in a single metadata instruction and parses it into an instructino object that can be
 * added to the set of instructions to eventually run
 */
void Metadata::addMetadata(string metadata)
{
  vector<string> tokens;
  Instruction newInstruction;

  // trim whitespace from the metadata string
  removeExtraWhitespace(metadata);


  cout << "metadata: " << metadata << endl;


  // split metadata into separate tokens, split up by ( and )
  splitString(metadata, '(', ')', tokens);

  // add fields to a new metadata struct object
  newInstruction.code = tokens[0][0];
  newInstruction.descriptor = tokens[1];
  newInstruction.cycles = stoi(tokens[2]);

  // push this new metadata into the list of instructions
  instructions.insert(instructions.begin(), newInstruction);
}


