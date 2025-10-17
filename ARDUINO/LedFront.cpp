#include "LedFront.h"
#include <Arduino.h>
///////////////////////////
LedFront::LedFront()  // Constructor
{   
}
//__________________________________________________________________________________________________________________________________________________________________
void LedFront::init(void)
{
   pinMode(PIN_LED_R,OUTPUT);
   pinMode(PIN_LED_G,OUTPUT);
   pinMode(PIN_LED_Y,OUTPUT);
   pinMode(PIN_LED_V,OUTPUT);

   digitalWrite(PIN_LED_R, HIGH);
   digitalWrite(PIN_LED_Y, HIGH);
   digitalWrite(PIN_LED_V, HIGH);
   digitalWrite(PIN_LED_G, HIGH);
}
//__________________________________________________________________________________________________________________________________________________________________
void LedFront::test(void)
{
  for(int i=0;i<3;i++)
  {
    digitalWrite(PIN_LED_R, LOW);
    digitalWrite(PIN_LED_Y, LOW);
    digitalWrite(PIN_LED_V, LOW);
    digitalWrite(PIN_LED_G, LOW);
    delay(250);
    digitalWrite(PIN_LED_R, HIGH);
    digitalWrite(PIN_LED_Y, HIGH);
    digitalWrite(PIN_LED_V, HIGH);
    digitalWrite(PIN_LED_G, HIGH);
    delay(250);
  }
}
//__________________________________________________________________________________________________________________________________________________________________
void LedFront::healthy(void)
{
  digitalWrite(PIN_LED_R, HIGH);
  digitalWrite(PIN_LED_Y, HIGH);
  digitalWrite(PIN_LED_V, HIGH);
  digitalWrite(PIN_LED_G, LOW);
}
//__________________________________________________________________________________________________________________________________________________________________
void LedFront::ok(void)
{
    digitalWrite(PIN_LED_R, HIGH);
    digitalWrite(PIN_LED_Y, LOW);
    digitalWrite(PIN_LED_V, HIGH);
    digitalWrite(PIN_LED_G, HIGH);
}
//__________________________________________________________________________________________________________________________________________________________________
void LedFront::abnormal(void)
{
    digitalWrite(PIN_LED_R, HIGH);
    digitalWrite(PIN_LED_Y, HIGH);
    digitalWrite(PIN_LED_V, LOW);
    digitalWrite(PIN_LED_G, HIGH);
}
//__________________________________________________________________________________________________________________________________________________________________
void LedFront::error(void)
{
    digitalWrite(PIN_LED_R, LOW);
    digitalWrite(PIN_LED_Y, HIGH);
    digitalWrite(PIN_LED_V, HIGH);
    digitalWrite(PIN_LED_G, HIGH);
}
//__________________________________________________________________________________________________________________________________________________________________







