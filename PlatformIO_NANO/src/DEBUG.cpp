#include <Arduino.h>
#include "DEBUG.h"
//_____________________________________________________________________________________________________________________________________________________________________

/**
 * @brief Brief description of the function/class
 * @param param1 Description of first parameter
 * @param param2 Description of second parameter
 * @return Description of return value
 */
debug::debug(double BaudRate){
  baud_rate=BaudRate;
}
//_____________________________________________________________________________________________________________________________________________________________________
/**
 * @brief Brief description of the function/class
 * @param param1 Description of first parameter
 * @param param2 Description of second parameter
 * @return Description of return value
 */
void debug::begin(void){
    Serial.begin(baud_rate); 
}
//_____________________________________________________________________________________________________________________________________________________________________
void debug::show(String msg){
  Serial.println(msg);
}
//_____________________________________________________________________________________________________________________________________________________________________
void debug::print(String msg){
  Serial.println(msg);
}
//_____________________________________________________________________________________________________________________________________________________________________
void debug::show(int val){
  Serial.println(val);
}
//_____________________________________________________________________________________________________________________________________________________________________
