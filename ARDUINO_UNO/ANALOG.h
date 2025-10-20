#ifndef ANALOG_H
#define ANALOG_H
#include <Arduino.h>
/////////////////////////
class analog{

  private:
    byte analog_PIN;

  public:
    analog(byte pin);
    void begin(void);
    unsigned int GetValue(void);
   
};





#endif