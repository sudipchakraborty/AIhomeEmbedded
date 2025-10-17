#include "Rtc1307.h"
#include <Arduino.h>
///////////////////////////
Rtc1307::Rtc1307()  // Constructor
{   
}
//__________________________________________________________________________________________________________________________________________________________________
void Rtc1307::init(void)
{
    count_Reg=0;
    compare_val=0; 
}
//__________________________________________________________________________________________________________________________________________________________________
 void Rtc1307::set(long val)
{
    compare_val=val;  
    count_Reg=0;
}
//__________________________________________________________________________________________________________________________________________________________________
bool Rtc1307::over(void)
{
   if(count_Reg>=compare_val)  
   {
      count_Reg=0;
      return true;
   }
   else
   {
      count_Reg++;
      return false;
   }
}
//__________________________________________________________________________________________________________________________________________________________________








// #include <Wire.h>
// #include <RTClib.h>


// //adafruit RTClib
// // Create an RTC_DS1307 object
// RTC_DS1307 rtc;

// void setup() {
//   Serial.begin(9600); // Initialize serial communication
//   Wire.begin();       // Initialize I2C communication

//   if (!rtc.begin()) {
//     Serial.println("Couldn't find RTC");
//     while (1); // Stop the program if RTC is not found
//   }

//   if (!rtc.isrunning()) {
//     Serial.println("RTC is NOT running, setting the time!");

//     // Set the date and time to the current time
//     rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
//   }
// }

// void loop() {
//   // Get the current time
//   DateTime now = rtc.now();

//   // Print the date and time in a readable format
//   Serial.print("Date: ");
//   Serial.print(now.year(), DEC);
//   Serial.print('/');
//   Serial.print(now.month(), DEC);
//   Serial.print('/');
//   Serial.print(now.day(), DEC);

//   Serial.print("  Time: ");
//   Serial.print(now.hour(), DEC);
//   Serial.print(':');
//   Serial.print(now.minute(), DEC);
//   Serial.print(':');
//   Serial.println(now.second(), DEC);

//   delay(1000); // Wait for 1 second
// }












