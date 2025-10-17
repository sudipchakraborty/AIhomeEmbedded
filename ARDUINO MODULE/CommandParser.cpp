#include "CommandParser.h"
#include <Arduino.h>
///////////////////////////
CommandParser::CommandParser()  // Constructor
{   
}
//__________________________________________________________________________________________________________________________________________________________________
/**
 * @brief init Function 
 * @param  
 * @param 
 * @return void
 */
void CommandParser::init(void)
{
   pinMode(LED_BUILTIN, OUTPUT);
   Serial.begin(115200);
   Serial.println("Enter command (separated by space or comma):");   
}
//__________________________________________________________________________________________________________________________________________________________________
/**
 * @brief Function check user press any command 
 * @param void
 * @param void
 * @return void
 */
void CommandParser::handle(void)
{
     // Read serial data non-blocking
  while (Serial.available() > 0 && !commandReady) 
  {
    char incomingChar = Serial.read();

    if (incomingChar == '\n')
     {
      commandBuffer[bufferIndex] = '\0'; // Null-terminate the string
      commandReady = true;               // Command is ready
    } 
    else if (bufferIndex < MAX_COMMAND_LENGTH - 1) 
    {
      commandBuffer[bufferIndex++] = incomingChar;
    }
  }
}
//__________________________________________________________________________________________________________________________________________________________________
/**
 * @brief Function to check any is present int the cue or buffer
 * @param void
 * @param void
 * @return bool true if present else false
 */
bool CommandParser::available(void)
{
  if(commandReady)
  {
    process();
    return true;
  }
  else return false;
}
//__________________________________________________________________________________________________________________________________________________________________
/**
 * @brief Function to Process the command when ready
 * @param void
 * @param void
 * @return void
 */
void CommandParser::process(void)
{
    String command = String(commandBuffer);
    command.trim(); // Remove leading and trailing whitespace

    // Parse the command
    numParts = parseCommand(command, parsedParts, MAX_PARTS);

    // // Print parsed parts
    // Serial.println("Parsed command parts:");
    // for (int i = 0; i < numParts; i++) {
    //   Serial.print("Part ");
    //   Serial.print(i);
    //   Serial.print(": ");
    //   Serial.println(parsedParts[i]);
    // }

    // Reset for next command
    bufferIndex = 0;
    commandReady = false;
    Serial.println("command:");
}
//__________________________________________________________________________________________________________________________________________________________________
/**
 * @brief Function to parse the content
 * @param void
 * @param void
 * @return void
 */
int CommandParser::parseCommand(String command, String parts[], int maxParts)
{
  int count = 0; // Counter for parts

  while (command.length() > 0 && count < maxParts) {
    int separatorIndex = findSeparatorIndex(command); // Find the next separator index
    if (separatorIndex == -1) {
      // If no separator is found, the rest of the command is a part
      parts[count++] = command;
      break;
    } else {
      // Extract the part before the separator
      parts[count++] = command.substring(0, separatorIndex);
      // Remove the extracted part from the command
      command = command.substring(separatorIndex + 1);
      command.trim(); // Remove extra spaces or commas
    }
  }
  return count; // Return the number of parts parsed
}
//__________________________________________________________________________________________________________________________________________________________________
/**
 * @brief Function to find the index of the next separator (space or comma)
 * @param void
 * @param void
 * @return void
 */
int CommandParser::findSeparatorIndex(String command) 
{
  int spaceIndex = command.indexOf(' '); // Index of the first space
  int commaIndex = command.indexOf(','); // Index of the first comma

  if (spaceIndex == -1) return commaIndex; // No space, return comma index
  if (commaIndex == -1) return spaceIndex; // No comma, return space index
  return min(spaceIndex, commaIndex);      // Return the smaller index (nearest separator)
}
//__________________________________________________________________________________________________________________________________________________________________
