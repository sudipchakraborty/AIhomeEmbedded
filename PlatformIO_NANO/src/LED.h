#ifndef LED_H
#define LED_H
#include <Arduino.h>
/////////////////////
class led{

  private:
    byte pin;
    bool logic;
    bool pinState = false;
  public:
    led(byte led_pin);
    void begin(void);
    void on(void);
    void off(void);
    void toggle(void); 
    void flash(void);
};
//////////////////////
#endif