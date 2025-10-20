#include "ANALOG.h"
#include <Arduino.h>


//______________________________________________________________________________________________________________________________________________
/**
 * @brief Brief description of the function/class
 * @param param1 Description of first parameter
 * @param param2 Description of second parameter
 * @return Description of return value
 */
analog::analog(byte pin){
  analog_PIN=pin;
}
//______________________________________________________________________________________________________________________________________________
 /**
 * @brief Brief description of the function/class
 * @param param1 Description of first parameter
 * @param param2 Description of second parameter
 * @return Description of return value
 */
 void analog::begin(void){
  pinMode(analog_PIN, INPUT);
  analogReference(DEFAULT);
}
//______________________________________________________________________________________________________________________________________________
/**
 * @brief Brief description of the function/class
 * @param param1 Description of first parameter
 * @param param2 Description of second parameter
 * @return Description of return value
 */
unsigned int analog:: GetValue(void){
   return analogRead(analog_PIN);
}
//______________________________________________________________________________________________________________________________________________












