#include "Profile.h"
#include <Arduino.h>
#include <ArduinoJson.h>
///////////////////////////
Profile::Profile()  // Constructor
{   
}
//__________________________________________________________________________________________________________________________________________________________________
void Profile::init(void)
{
    
}
//__________________________________________________________________________________________________________________________________________________________________
String Profile::get(char id)
{
  StaticJsonDocument<256> doc;

    switch(id)
    {
        case 'A':
          doc["Relay_1"] = "on";
          doc["Relay_2"] = "on";
          doc["Relay_3"] = "on";
          doc["Relay_4"] = "on";
          doc["Relay_5"] = "on";
          doc["Relay_6"] = "on";
          doc["Relay_7"] = "on";
          doc["Relay_8"] = "on";
        break;
        /////////////////////////
         case 'C':
          doc["Relay_1"] = "off";
          doc["Relay_2"] = "off";
          doc["Relay_3"] = "off";
          doc["Relay_4"] = "off";
          doc["Relay_5"] = "off";
          doc["Relay_6"] = "off";
          doc["Relay_7"] = "off";
          doc["Relay_8"] = "off";
        break;
        /////////////////////////
        case '1':
          doc["Relay_1"] = "on";
          doc["Relay_2"] = "off";
          doc["Relay_3"] = "off";
          doc["Relay_4"] = "off";
          doc["Relay_5"] = "off";
          doc["Relay_6"] = "off";
          doc["Relay_7"] = "off";
          doc["Relay_8"] = "off";
        break;
        /////////////////////////
        case '2':
          doc["Relay_1"] = "off";
          doc["Relay_2"] = "on";
          doc["Relay_3"] = "off";
          doc["Relay_4"] = "off";
          doc["Relay_5"] = "off";
          doc["Relay_6"] = "off";
          doc["Relay_7"] = "off";
          doc["Relay_8"] = "off";
        break;
        /////////////////////////
        case '3':
          doc["Relay_1"] = "off";
          doc["Relay_2"] = "off";
          doc["Relay_3"] = "on";
          doc["Relay_4"] = "off";
          doc["Relay_5"] = "off";
          doc["Relay_6"] = "off";
          doc["Relay_7"] = "off";
          doc["Relay_8"] = "off";
        break;
        /////////////////////////
        case '4':
          doc["Relay_1"] = "off";
          doc["Relay_2"] = "off";
          doc["Relay_3"] = "off";
          doc["Relay_4"] = "on";
          doc["Relay_5"] = "off";
          doc["Relay_6"] = "off";
          doc["Relay_7"] = "off";
          doc["Relay_8"] = "off";
        break;
        /////////////////////////
        case '5':
          doc["Relay_1"] = "off";
          doc["Relay_2"] = "off";
          doc["Relay_3"] = "off";
          doc["Relay_4"] = "off";
          doc["Relay_5"] = "on";
          doc["Relay_6"] = "off";
          doc["Relay_7"] = "off";
          doc["Relay_8"] = "off";
        break;
        /////////////////////////
        case '6':
          doc["Relay_1"] = "off";
          doc["Relay_2"] = "off";
          doc["Relay_3"] = "off";
          doc["Relay_4"] = "off";
          doc["Relay_5"] = "off";
          doc["Relay_6"] = "on";
          doc["Relay_7"] = "off";
          doc["Relay_8"] = "off";
        break;
        /////////////////////////
        case '7':
          doc["Relay_1"] = "off";
          doc["Relay_2"] = "off";
          doc["Relay_3"] = "off";
          doc["Relay_4"] = "off";
          doc["Relay_5"] = "off";
          doc["Relay_6"] = "off";
          doc["Relay_7"] = "on";
          doc["Relay_8"] = "off";
        break;
        /////////////////////////
        case '8':
          doc["Relay_1"] = "off";
          doc["Relay_2"] = "off";
          doc["Relay_3"] = "off";
          doc["Relay_4"] = "off";
          doc["Relay_5"] = "off";
          doc["Relay_6"] = "off";
          doc["Relay_7"] = "off";
          doc["Relay_8"] = "on";
        break;
        /////////////////////////
        default:
        break;
    }
     String jsonOutput;
     serializeJson(doc, jsonOutput);
     return jsonOutput;
}
//__________________________________________________________________________________________________________________________________________________________________