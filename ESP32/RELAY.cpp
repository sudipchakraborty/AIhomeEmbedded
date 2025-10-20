#include "Relay.h"
#include <Arduino.h>
#include <ArduinoJson.h>
///////////////////////////
Relay::Relay()  // Constructor
{   
}
//__________________________________________________________________________________________________________________________________________________________________
void Relay::init(void)
{
   pinMode(Relay_1,OUTPUT);
   pinMode(Relay_2,OUTPUT);
   pinMode(Relay_3,OUTPUT);
   pinMode(Relay_4,OUTPUT);
   pinMode(Relay_5,OUTPUT);
   pinMode(Relay_6,OUTPUT);
   pinMode(Relay_7,OUTPUT);
   pinMode(Relay_8,OUTPUT);
   ///////////////////////
   digitalWrite(Relay_1, HIGH);
   digitalWrite(Relay_2, HIGH);
   digitalWrite(Relay_3, HIGH);
   digitalWrite(Relay_4, HIGH);
   digitalWrite(Relay_5, HIGH);
   digitalWrite(Relay_6, HIGH);
   digitalWrite(Relay_7, HIGH);
   digitalWrite(Relay_8, HIGH);

}
//__________________________________________________________________________________________________________________________________________________________________
void Relay::update(String str)
{
  // Allocate JSON document
  StaticJsonDocument<200> doc;

  // Deserialize the JSON document
  DeserializationError error = deserializeJson(doc, str);

   // Extract values
    const char* RL1 = doc["Relay_1"];
    const char* RL2 = doc["Relay_2"];
    const char* RL3 = doc["Relay_3"];
    const char* RL4 = doc["Relay_4"];
    const char* RL5 = doc["Relay_5"];
    const char* RL6 = doc["Relay_6"];
    const char* RL7 = doc["Relay_7"];
    const char* RL8 = doc["Relay_8"];

   if(strcmp(RL1, "on") == 0) digitalWrite(Relay_1, LOW); else  digitalWrite(Relay_1, HIGH); 
   if(strcmp(RL2, "on") == 0) digitalWrite(Relay_2, LOW); else  digitalWrite(Relay_2, HIGH); 
   if(strcmp(RL3, "on") == 0) digitalWrite(Relay_3, LOW); else  digitalWrite(Relay_3, HIGH); 
   if(strcmp(RL4, "on") == 0) digitalWrite(Relay_4, LOW); else  digitalWrite(Relay_4, HIGH); 
   if(strcmp(RL5, "on") == 0) digitalWrite(Relay_5, LOW); else  digitalWrite(Relay_5, HIGH); 
   if(strcmp(RL6, "on") == 0) digitalWrite(Relay_6, LOW); else  digitalWrite(Relay_6, HIGH); 
   if(strcmp(RL7, "on") == 0) digitalWrite(Relay_7, LOW); else  digitalWrite(Relay_7, HIGH); 
   if(strcmp(RL8, "on") == 0) digitalWrite(Relay_8, LOW); else  digitalWrite(Relay_8, HIGH);
}
//__________________________________________________________________________________________________________________________________________________________________