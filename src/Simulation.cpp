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

  logToMonitor = false;
  logToFile = false;
  logFilePath = "";
}

Simulation::~Simulation()
{

}


/*
 * Get the path for the metadata file
 */
string Simulation::getMetadataFilePath()
{
  return mdf_filePath;
}


/*
 * Get the desired cycle time for a device based on
 * the code and the descriptor provided
 */
int Simulation::getCycleTime(char code, string descriptor)
{
  int cycleTime = 0;

  // determine which cycle time to return, based on the code
  switch(code)
  {
    // case P
    case 'P':

      if( descriptor == "run" )
      {
        cycleTime = processorCycleTime;
      }
      break;

    // case I
    case 'I':

      if( descriptor == "hard drive" )
      {
        cycleTime = hardDriveCycleTime;
      }
      else if( descriptor == "monitor")
      {
        cycleTime = monitorDisplayTime;
      }
      else if( descriptor == "keyboard")
      {
        cycleTime = keyboardCycleTime;
      }
      break;

    // case O
    case 'O':

      if( descriptor == "hard drive" )
      {
        cycleTime = hardDriveCycleTime;
      }
      else if( descriptor == "monitor")
      {
        cycleTime = monitorDisplayTime;
      }
      else if( descriptor == "printer" )
      {
        cycleTime = printerCycleTime;
      }
      break;

    // case M
    case 'M':

      if( descriptor == "allocate" )
      {
        cycleTime = memoryCycleTime;
      }
      else if( descriptor == "cache")
      {
        cycleTime = memoryCycleTime;
      }
      break;
  }

  return cycleTime;
}


/*
 * Provide a logger for output within this class
 */
void Simulation::setLogger(Logger *theLogger)
{
  logger = theLogger;
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

  // check if the file was read
  if( readFile == true ){

    // turn the logger on
    turnLoggerOn();

    // log the configuration of the simulation
    logSimulationSettings();
  }

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


/*
 * Enables logging on the logger
 */
void Simulation::turnLoggerOn()
{
  // check if monitor logging should be enabled
  if(logToMonitor)
  {
    logger->enableMonitorLogging();
  }

  // check if file logging should be enabled
  if(logToFile)
  {
    logger->enableLoggingToFile( logFilePath );
  }
}

/*
 * Output all settings from the simulation to the console
 */
void Simulation::logSimulationSettings()
{
  string message;
  vector<string> logfilePathTokens;

  // begin logging to the file
  logger->log("Configuration File Data");

  // log processor settings
  message = "Processor = " + to_string(processorCycleTime) + " ms/cycle";
  logger->log(message);

  // log monitor settings
  message = "Monitor = " + to_string(monitorDisplayTime) + " ms/cycle";
  logger->log(message);

  // log hard drive settings
  message = "Hard Drive = " + to_string(hardDriveCycleTime) + " ms/cycle";
  logger->log(message);

  // log printer settings
  message = "Printer = " + to_string(printerCycleTime) + " ms/cycle";
  logger->log(message);

  // log keyboard settings
  message = "Keyboard = " + to_string(keyboardCycleTime) + " ms/cycle";
  logger->log(message);

  // log memory settings
  message = "Memory = " + to_string(memoryCycleTime) + " ms/cycle";
  logger->log(message);

  // setup the message to log the settings on where the simulation is logging
  message = "Logged to: ";

  if(logToMonitor && logToFile)
  {
    // extract the filename from the filepath
    splitString(logFilePath, '/', logfilePathTokens);

    message += "monitor and " + logfilePathTokens[ logfilePathTokens.size() - 1 ];
  }
  else if(logToMonitor)
  {
    message += "monitor";
  }
  else if(logToFile)
  {
    // extract the filename from the filepath
    splitString(logFilePath, '/', logfilePathTokens);

    message += logfilePathTokens[ logfilePathTokens.size() - 1 ];
  }

  // finally, log where the simulation is logging
  logger->log(message);

  // log an empty line
  logger->log("");
}

