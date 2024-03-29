#ifndef OPERATING_SYSTEM_FILEPARSER_H
#define OPERATING_SYSTEM_FILEPARSER_H

/*
 * CLASS - FileParser
 *
 * ABOUT - Parent class for File Parsing objects. Contains
 *  helper functions that represent shared functionality
 *  between the file parsers.
 */

#include <fstream>
#include <vector>
#include <string>
#include <cstring>

using namespace std;

class FileParser
{
  public:
    FileParser();
    ~FileParser();

    void removeExtraWhitespace(string &str);
    void splitString(string theString, char delimiter, vector<string> &theSplitString);
    void splitString(string theString, char delimiter1, char delimiter2, vector<string> &theSplitString);
};

#endif //OPERATING_SYSTEM_FILEPARSER_H
