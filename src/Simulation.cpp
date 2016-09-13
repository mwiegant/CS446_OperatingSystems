#include "Simulation.h"

Simulation::Simulation()
{
  osVersion = 0.0f;
  mdf_filePath = "";
  cpuSchedulingCode = "";

  processorCycleTime = 0;
  monitorDisplayTime = 0;
  hardDriveCycleTime = 0;
  printerCycleTime = 0;
  keyboardCycleTime = 0;
  memoryCycleTime = 0;
  systemMemory = 0;

  logToConsole = false;
  logToFile = false;
  logFilePath = "";
}

Simulation::~Simulation()
{

}


/*
 * --- BEGIN - GETTERS ---
 */
string Simulation::getMetadataFilePath()
{
  return mdf_filePath;
}

int Simulation::getProcessorCycleTime()
{
  return processorCycleTime;
}

int Simulation::getMonitorDisplayTime()
{
  return monitorDisplayTime;
}

int Simulation::getHardDriveCycleTime()
{
  return hardDriveCycleTime;
}

int Simulation::getPrinterCycleTime()
{
  return printerCycleTime;
}

int Simulation::getKeyboardCycleTime()
{
  return keyboardCycleTime;
}

int Simulation::getMemoryCycleTime()
{
  return memoryCycleTime;
}
/*
 * --- END - GETTERS ---
 */


/*
 * Output all settings from the simulation to the console
 */
void Simulation::showSimulationSettings()
{
  string _logToFile = (logToFile) ? "yes" : "no";
  string _logToMonitor = (logToConsole) ? "yes" : "no";


  fprintf(stdout, "Simulation Settings\n");
  fprintf(stdout, "-------------------\n");
  fprintf(stdout, "osVersion          : %f\n", osVersion);
  fprintf(stdout, "msf_filePath       : %s\n", mdf_filePath.c_str());
//  fprintf(stdout, "cpuSchedulingCode  : %s\n", cpuSchedulingCode.c_str());
  fprintf(stdout, "processorCycleTime : %d\n", processorCycleTime);
  fprintf(stdout, "monitorDisplayTime : %d\n", monitorDisplayTime);
  fprintf(stdout, "hardDriveCycleTime : %d\n", hardDriveCycleTime);
  fprintf(stdout, "printerCycleTime   : %d\n", printerCycleTime);
  fprintf(stdout, "keyboardCycleTime  : %d\n", keyboardCycleTime);
  fprintf(stdout, "memoryCycleTime    : %d\n", memoryCycleTime);
  fprintf(stdout, "systemMemory       : %d\n", systemMemory);
  fprintf(stdout, "log to monitor     : %s\n", _logToMonitor.c_str());
  fprintf(stdout, "log to file        : %s\n", _logToFile.c_str());
  fprintf(stdout, "logFilePath        : %s\n", logFilePath.c_str());

}


/*
 *  Reads in the config file, one line at a time.
 */
bool Simulation::readInConfig(char filePath[])
{
  ifstream fin;
  string linedata;
  bool readFile = false;

  // clear input file-stream flags and open the file
  fin.clear();
  fin.open(filePath);

  while( fin.good() )
  {
    readFile = true;

    // get one line at a time
    getline(fin, linedata, '\n');

    // send the line to data extraction function
    extractData(linedata);

  }

  fin.close();

  return readFile;
}


/*
 * Given a line of data from the config data, splits the line up and passes
 * the split up line to a final processing function to store data into the Simulation
 */
void Simulation::extractData(string fileData)
{
  vector<string> splitData;
  int vectorSize;

  // split the string at whitespaces
  splitString(fileData, ' ', splitData);

  // get the number of tokens in the split string
  vectorSize = splitData.size();

  // send the first and last token of the split string to a processing function
  processData(splitData[0], splitData[vectorSize - 1]);
}


/*
 * Given a label and some data, determines which part of the Simulation to update
 * with the new data
 */
void Simulation::processData(string label, string data)
{
  // process version
  if( label == "Version/Phase:")
  {
    osVersion = stof(data);
  }

  // process metadata file path
  else if( label == "File")
  {
    mdf_filePath = data;
  }

  // process processor cycle time
  else if( label == "Processor")
  {
    processorCycleTime = stoi(data);
  }

  // process monitor display time
  else if( label == "Monitor")
  {
    monitorDisplayTime = stoi(data);
  }

  // process hard drive cycle time
  else if( label == "Hard")
  {
    hardDriveCycleTime = stoi(data);
  }

  // process printer cycle time
  else if( label == "Printer")
  {
    printerCycleTime = stoi(data);
  }

  // process keyboard cycle time
  else if( label == "Keyboard")
  {
    keyboardCycleTime = stoi(data);
  }

  // process memory cycle time
  else if( label == "Memory")
  {
    memoryCycleTime = stoi(data);
  }

  // process system memory
  else if( label == "System")
  {
    systemMemory = stoi(data);
  }

  // process where to log
  else if( label == "Log:")
  {
    // determine where to log, based on the value of data
    if(data == "Both")
    {
      logToConsole = true;
      logToFile = true;
    }
    else if(data == "File")
    {
      logToFile = true;
    }
    else if(data == "Monitor")
    {
      logToConsole = true;
    }
  }

  // process log file path
  else if( label == "Log")
  {
    logFilePath = data;
  }


}


/*
 * Utility function for splitting up a string into a number of tokens, where each
 * token is split up where the delimiter character is found in the larger string
 */
void Simulation::splitString(string theString, char delimiter, vector<string> &theSplitString)
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