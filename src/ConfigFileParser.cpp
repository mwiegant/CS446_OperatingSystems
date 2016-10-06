#include "ConfigFileParser.h"


ConfigFileParser::ConfigFileParser()
{

  /* Set default values for the Config properties */

  osVersion = 0.0f;
  cpuSchedulingCode = "";

  processorCycleTime = 0;
  monitorDisplayTime = 0;
  hardDriveCycleTime = 0;
  printerCycleTime = 0;
  keyboardCycleTime = 0;
  memoryCycleTime = 0;
  systemMemory = 0;

  logToMonitor = false;
  logToFile = false;
  logFileName = "";
  logFilePath = "";
}


ConfigFileParser::~ConfigFileParser()
{

}


/*
 *  Reads in the config file, one line at a time.
 */
bool ConfigFileParser::readInConfig(char filePath[])
{
  ifstream fin;
  string linedata;
  bool readTheFile = false;

  // clear input file-stream flags and open the file
  fin.clear();
  fin.open(filePath);

  while( fin.good() )
  {
    readTheFile = true;

    // get one line at a time
    getline(fin, linedata, '\n');

    // send the line to data extraction function
    extractData(linedata);
  }

  fin.close();

  return readTheFile;
}


/*
 * Given a line of data from the config data, splits the line up and passes
 * the split up line to a final processing function to store data into the Simulation
 */
void ConfigFileParser::extractData(string fileData)
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
void ConfigFileParser::processData(string label, string data)
{
  vector<string> logfilePathTokens;

  printf("Label: %s\n", label.c_str());

  // process version
  if( label == "Version/Phase:")
  {
    osVersion = stof(data);
  }

  // process metadata file path
  else if( label == "File")
  {
    strcpy( mdf_filePath, data.c_str() );
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
      logToMonitor = true;
      logToFile = true;
    }
    else if(data == "File")
    {
      logToFile = true;
    }
    else if(data == "Monitor")
    {
      logToMonitor = true;
    }

  }

  // process log file path
  else if( label == "Log")
  {
    // extract the filename from the filepath
    splitString(data, '/', logfilePathTokens);

    logFilePath = data;
    logFileName = logfilePathTokens[1];
  }


}


/*
 * Getters
 */

void ConfigFileParser::getOSVersion(float& osVersion)
{
  osVersion = this->osVersion;
}

void ConfigFileParser::getMetaFilePath(char metaFilePath[])
{
  strcpy( metaFilePath, this->mdf_filePath );
}

void ConfigFileParser::getSchedulingCode(string& schedulingCode)
{
  schedulingCode = this->cpuSchedulingCode;
}

void ConfigFileParser::getProcessorCycleTime(int& cycleTime)
{
  cycleTime = this->processorCycleTime;
}

void ConfigFileParser::getMonitorCycleTime(int& cycleTime)
{
  cycleTime = this->monitorDisplayTime;
}

void ConfigFileParser::getHardDriveCycleTime(int& cycleTime)
{
  cycleTime = this->hardDriveCycleTime;
}

void ConfigFileParser::getPrinterCycleTime(int& cycleTime)
{
  cycleTime = this->printerCycleTime;
}

void ConfigFileParser::getKeyboardCycleTime(int& cycleTime)
{
  cycleTime = this->keyboardCycleTime;
}

void ConfigFileParser::getMemoryCycleTime(int& cycleTime)
{
  cycleTime = this->memoryCycleTime;
}

void ConfigFileParser::getSystemMemory(int& systemMemory)
{
  systemMemory = this->systemMemory;
}

void ConfigFileParser::getLoggingInformation(bool& logToMonitor, bool& logToFile, string& logFileName, string& logFilePath)
{
  logToMonitor = this->logToMonitor;
  logToFile = this->logToFile;
  logFileName = this->logFileName;
  logFilePath = this->logFilePath;
}









