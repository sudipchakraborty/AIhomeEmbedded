#include "FND.h"

#include <Arduino.h>

#define analogPin A0

// module
fnd display(13, 12, 11);  

//_____________________________________________________________________________________________________________________________________________________________________________________________________--
void setup() {
  display.begin();
  Serial.begin(9600); 
  pinMode(analogPin, INPUT);
  analogReference(DEFAULT);
}
//_____________________________________________________________________________________________________________________________________________________________________________________________________--
void loop() {
  // Read analog value (0-1023)
  int analogValue = analogRead(analogPin);

   display.displayMultiDigit(analogValue);
  
  // // Convert to voltage (0-5V) or display raw value
  // // Here we'll display the raw value (0-1023)
  // displayMultiDigit(analogValue);
  // Serial.println(analogValue);
  
  // delay(100); // Update every 100ms
}
//_____________________________________________________________________________________________________________________________________________________________________________________________________--
