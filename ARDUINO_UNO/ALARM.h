#ifndef ALARM_H
#define ALARM_H
#include <Arduino.h>
////////////////////
class alarm{
  private:
    byte pin;
  public:
  alarm(byte AlarmPin);
  void begin(void);
  void on(void);
  void off(void);
};





#endif