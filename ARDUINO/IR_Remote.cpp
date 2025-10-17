#include "IR_Remote.h"
#include <Arduino.h>
#include <IRremote.h> //IRremote by shirriff,z3t0,ArminJo
// ///////////////////////////

// ////////////////////////////////
const int RECV_PIN = 2;
IRrecv irrecv(RECV_PIN);
decode_results results;
// //////////////////////////////
IR_Remote::IR_Remote()  // Constructor
{   
}
//__________________________________________________________________________________________________________________________________________________________________
void IR_Remote::init(void)
{
    IrReceiver.begin(RECV_PIN, ENABLE_LED_FEEDBACK);
    Serial.println("Ready to decode IR signals...");
}
//__________________________________________________________________________________________________________________________________________________________________
bool IR_Remote::pressed(void)
{ 
    if (IrReceiver.decode())  
     {
        unsigned long rawData = IrReceiver.decodedIRData.decodedRawData;
        char hexString[11];
        sprintf(hexString, "0x%08lX", rawData);
        strCode = String(hexString);
        IrReceiver.resume();
        return true;
     }
     else
     {
        return false;
     }
}
//__________________________________________________________________________________________________________________________________________________________________
char IR_Remote::get(void)
{
  if (strCode == BTN_1)  return '1';
  if (strCode == BTN_2)  return '2';
  if (strCode == BTN_3)  return '3';
  if (strCode == BTN_4)  return '4';
  if (strCode == BTN_5)  return '5';
  if (strCode == BTN_6)  return '6';
  if (strCode == BTN_7)  return '7';
  if (strCode == BTN_8)  return '8';
  if (strCode == BTN_9)  return '9';
  if (strCode == BTN_0)  return '0';

  if (strCode == BTN_MUTE)  return 'A';
  if (strCode == BTN_PWR)   return 'C';     
}
// //__________________________________________________________________________________________________________________________________________________________________