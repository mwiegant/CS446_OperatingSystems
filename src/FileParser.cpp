#include "FileParser.h"

FileParser::FileParser()
{

}

FileParser::~FileParser()
{

}


/*
 * Utility function for splitting up a string into a number of tokens, where each
 * token is split up where the delimiter character is found in the larger string
 */
void FileParser::splitString(string theString, char delimiter, vector<string> &theSplitString)
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


/*
 * Utility function for splitting up a string into a number of tokens, where each
 * token is split up where the delimiter character is found in the larger string
 */
void FileParser::splitString(string theString, char delimiter1, char delimiter2, vector<string> &theSplitString)
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
void FileParser::removeExtraWhitespace(string &str)
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