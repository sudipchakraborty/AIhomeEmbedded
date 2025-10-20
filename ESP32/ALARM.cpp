#include "ALARM.h"
#include <Arduino.h>

//________________________________________________________________________________________________________________________________________________________________
/**
 * @brief Brief description of the function/class
 * @param param1 Description of first parameter
 * @param param2 Description of second parameter
 * @return Description of return value
 */
alarm::alarm(byte AlarmPin)
{
  pin=AlarmPin;
}
//________________________________________________________________________________________________________________________________________________________________
/**
 * @brief Brief description of the function/class
 * @param param1 Description of first parameter
 * @param param2 Description of second parameter
 * @return Description of return value
 */
void alarm::begin(void)
{
    //  pinMode(pin, OUTPUT);
}
//________________________________________________________________________________________________________________________________________________________________
/**
 * @brief Brief description of the function/class
 * @param param1 Description of first parameter
 * @param param2 Description of second parameter
 * @return Description of return value
 */
void alarm::on(void)
{
    digitalWrite(pin, HIGH);
}
//________________________________________________________________________________________________________________________________________________________________
/**
 * @brief Brief description of the function/class
 * @param param1 Description of first parameter
 * @param param2 Description of second parameter
 * @return Description of return value
 */
void alarm::off(void)
{
    digitalWrite(pin, LOW);
}
//________________________________________________________________________________________________________________________________________________________________



















