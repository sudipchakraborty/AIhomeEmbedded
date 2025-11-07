#ifndef LED_H
#define LED_H
#include <Arduino.h>
/////////////////////
class led{

  private:
    byte pin;
    bool logic=1;
    bool pinState = false;
  public:
    led(byte led_pin);
    led(byte led_pin, bool logic_state);
    void begin(void);
    void on(void);
    void off(void);
    void toggle(void); 
    void toggle(long delayVal); 
    void flash(void);
};
//////////////////////
#endif