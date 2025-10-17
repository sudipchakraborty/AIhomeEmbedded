#ifndef COMMANDPARSER_H
#define COMMANDPARSER_H
#include <Arduino.h>
//////////////////////

#define MAX_COMMAND_LENGTH 50   // Maximum command length
#define MAX_PARTS         10    // Maximum number of parts to parse


////////////////////////////////////////
class CommandParser
{
    public:
           CommandParser();
      void init(void);
      void handle();
      bool available(void);
      void CommandParser::process(void);
      int parseCommand(String command, String parts[], int maxParts);
      int findSeparatorIndex(String command);
      String parsedParts[MAX_PARTS];          // Array to store parsed parts
      int numParts = 0;                       // Number of parts parsed
      char commandBuffer[MAX_COMMAND_LENGTH]; // Buffer for incoming command
      int bufferIndex = 0;                    // Index for buffer
      bool commandReady = false;              // Flag for complete command   
    private: 
     
};
///////////////////////











#endif
