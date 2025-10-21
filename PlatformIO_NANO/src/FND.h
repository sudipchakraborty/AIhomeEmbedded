#ifndef FND_H
#define FND_H
#include "Arduino.h"
////////////////////////////

//____________________________________________________________________________________________________________________________________________________________________________________________
class fnd{

  private:
    byte dataPin;
    byte clockPin;
    byte strobePin;
  public:
    // Constructor
    fnd(byte data, byte clock, byte latch);
    void begin();
    void displayValue(int value);
    void shiftOut(int data);
    void displayMultiDigit(int number);
    void shiftOutByte(uint8_t data);
};
//____________________________________________________________________________________________________________________________________________________________________________________________








#endif