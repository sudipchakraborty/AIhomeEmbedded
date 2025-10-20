#include "FND.h"
#include <Arduino.h>
//____________________________________________________________________________________________________________________________________________________________________________________________
int digitPatterns[10] = {
  0x3F, // 0
  0x06, // 1
  0x5B, // 2
  0x4F, // 3
  0x66, // 4
  0x6D, // 5
  0x7D, // 6
  0x07, // 7
  0x7F, // 8
  0x6F  // 9
};
//____________________________________________________________________________________________________________________________________________________________________________________________
// Constructor
fnd::fnd(byte data, byte clock, byte latch) {
    dataPin = data;
    clockPin = clock;
    strobePin = latch;
}
// //____________________________________________________________________________________________________________________________________________________________________________________________
// Initialize pins
void fnd::begin() {
    pinMode(dataPin, OUTPUT);
    pinMode(clockPin, OUTPUT);
    pinMode(strobePin, OUTPUT);
}
//_____________________________________________________________________________________________________________________________________________________________________________________________________--
void fnd::displayMultiDigit(int number) {
  number = constrain(number, 0, 999);
  
  int digits[] = {
    number / 100,           // Hundreds
    (number % 100) / 10,    // Tens  
    number % 10             // Units
  };
  
  digitalWrite(strobePin, LOW);
  for(int i = 0; i < 3; i++) {
    // Select digit i
     shiftOutByte(digitPatterns[digits[i]]); //to shift register
    // Small delay
  }
    digitalWrite(strobePin, HIGH);
}
//_____________________________________________________________________________________________________________________________________________________________________________________________________--
// Internal bit-banging function (no name clash)
void fnd::shiftOutByte(uint8_t data) {
  for (int i = 7; i >= 0; i--) {
    digitalWrite(clockPin, LOW);
    // convert bit to HIGH or LOW
    if ( (data >> i) & 0x01 ) digitalWrite(dataPin, HIGH);
    else digitalWrite(dataPin, LOW);
    digitalWrite(clockPin, HIGH);
  }
}
//____________________________________________________________________________________________________________________________________________________________________________________________
