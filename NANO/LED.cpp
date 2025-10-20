#include "LED.h"
#include <Arduino.h>
//___________________________________________________________________________________________________________________________________________
/**
 * @brief this is the constructor of the led module
 * @param led_pin controller pin to connect led
 * @return none
 */
  led::led(byte led_pin){
  pin=led_pin;
}
//___________________________________________________________________________________________________________________________________________
/**
 * @brief set the pin as output
 * @param none
 * @return none
 */
  void led::begin(void){
  pinMode(pin, OUTPUT);
}
//___________________________________________________________________________________________________________________________________________
/**
 * @brief this is the constructor of the led module
 * @param led_pin controller pin to connect led
 * @return none
 */
  void led::on(void){
  digitalWrite(pin, HIGH);
  }
//___________________________________________________________________________________________________________________________________________
/**
 * @brief this is the constructor of the led module
 * @param led_pin controller pin to connect led
 * @return none
 */
  void led::off(void){
  digitalWrite(pin, LOW);
  }
//___________________________________________________________________________________________________________________________________________
/**
 * @brief this is the constructor of the led module
 * @param led_pin controller pin to connect led
 * @return none
 */
  void led::toggle(void){
  pinState = !pinState; 
  digitalWrite(pin, pinState);
}
//___________________________________________________________________________________________________________________________________________
/**
 * @brief this is the constructor of the led module
 * @param led_pin controller pin to connect led
 * @return none
 */
  void led::flash(void){
  digitalWrite(pin, HIGH);
  delay(250);
  digitalWrite(pin, LOW);
}
//___________________________________________________________________________________________________________________________________________




















