#include "SmartSwitchBoard.h"
#include <Arduino.h>
#include "buzzer.h"
#include "LedFront.h"
#include "Relay.h"
#include "Profile.h"
#include "IR_remote.h"
#include "Key44.h"
///////////////////////////
buzzer    bz;
LedFront  led;
Relay     rl;
Profile   pfl;
IR_Remote rmt;
Key44     key;
////////////////////////////
SmartSwitchBoard::SmartSwitchBoard()  // Constructor
{   
}
//__________________________________________________________________________________________________________________________________________________________________
void SmartSwitchBoard::init(void)
{
    bz.init(8);
    led.init();
    Serial.begin(115200);
    // bz.beep();
    led.test();

    rl.init();

    led.healthy();
    rmt.init();
    // key.init();
}
//__________________________________________________________________________________________________________________________________________________________________
void SmartSwitchBoard::handle(void)
{
    if(key.pressed())
    {
      bz.beep_key();
     // Serial.println(key.code);
      String str=pfl.get(key.code);
      Serial.println(str);
      rl.update(str);      
    }
    
    if(rmt.pressed())
    {
      char key=rmt.get();
      bz.beep_key();
    //  Serial.println(key);
      String str=pfl.get(key);
      Serial.println(str);
      rl.update(str);  
    }
}
//______________________________________________________________________________________________________________________________________________________________