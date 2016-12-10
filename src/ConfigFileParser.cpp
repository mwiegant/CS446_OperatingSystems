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

  memoryBlockSize = 128;
  hardDriveQuantity = 1;
  printerQuantity = 1;
  keyboardQuantity = 1;

  logToMonitor = false;
  logToFile = false;
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

/*
 * Given a line of data from the config data, splits the line up at every space, and sends
 * the first, second-to-last, and last tokens from the split-up line to the processData() function,
 * which looks at those tokens to determine which setting is being set in that line.
 */
void ConfigFileParser::extractData(string fileData)
{
  vector<string> splitData;
  int vectorSize;

  // split the string at whitespaces
  splitString(fileData, ' ', splitData);

  // get the number of tokens in the split string
  vectorSize = splitData.size();

  // send the first, second-to-last, and last token of the split string to a processing function
  processData(splitData[0], splitData[vectorSize - 2], splitData[vectorSize - 1]);
}


/*
 * Given two labels and some data, determines which part of the Simulation to update
 * with the new data.
 *
 * Ex:
 * Hard drive quantity: 2
 *
 * label1: Hard
 * label2: quantity
 * data:   2
 */
void ConfigFileParser::processData(string label1, string label2, string data)
{
  vector<string> logfilePathTokens;

  // process version
  if( label1 == "Version/Phase:")
  {
    osVersion = stof(data);
  }

  // process metadata file path
  else if( label1 == "File")
  {
    strcpy( mdf_filePath, data.c_str() );
  }

  // process memory block size
  else if( label1 == "Memory" && label2 == "(kbytes):")
  {
    memoryBlockSize = stoi(data);
  }

  // process hard drive quantity
  else if( label1 == "Hard" && label2 == "quantity:")
  {
    hardDriveQuantity = stoi(data);
  }

  // process printer quantity
  else if( label1 == "Printer" && label2 == "quantity:")
  {
    printerQuantity = stoi(data);
  }

  // process keyboard quantity
  else if( label1 == "Keyboard" && label2 == "quantity:")
  {
    keyboardQuantity = stoi(data);
  }

  // process processor cycle time
  else if( label1 == "Processor")
  {
    processorCycleTime = stoi(data);
  }

  // process monitor display time
  else if( label1 == "Monitor")
  {
    monitorDisplayTime = stoi(data);
  }

  // process hard drive cycle time
  else if( label1 == "Hard")
  {
    hardDriveCycleTime = stoi(data);
  }

  // process printer cycle time
  else if( label1 == "Printer")
  {
    printerCycleTime = stoi(data);
  }

  // process keyboard cycle time
  else if( label1 == "Keyboard")
  {
    keyboardCycleTime = stoi(data);
  }

  // process memory cycle time
  else if( label1 == "Memory")
  {
    memoryCycleTime = stoi(data);
  }

  // process system memory
  else if( label1 == "System")
  {
    systemMemory = stoi(data);
  }

  // process where to log
  else if( label1 == "Log:")
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
  else if( label1 == "Log")
  {
    printf("processing log file path, data: %s\n", data.c_str());

    // extract the filename from the filepath
    splitString(data, '/', logfilePathTokens);

    logFilePath = data;
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

void ConfigFileParser::getLoggingInformation(bool& logToMonitor, bool& logToFile, string& logFilePath)
{
  logToMonitor = this->logToMonitor;
  logToFile = this->logToFile;
  logFilePath = this->logFilePath;
}

void ConfigFileParser::getMemoryBlockSize(int& blockSize)
{
  blockSize = memoryBlockSize;
}

void ConfigFileParser::getDeviceQuantities(int& numHardDrives, int& numPrinters, int& numKeyboards)
{
  numHardDrives = hardDriveQuantity;
  numPrinters = printerQuantity;
  numKeyboards = keyboardQuantity;
}







