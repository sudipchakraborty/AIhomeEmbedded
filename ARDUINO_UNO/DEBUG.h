#ifndef DEBUG_H
#define DEBUG_H
#include <Arduino.h>

class debug{

  private:
  double baud_rate;
     
  public:
    debug(double BaudRate);
    void begin(void);
    void show(String msg);
    void show(int val);
};
#endif