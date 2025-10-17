#include "RtcDs3231.h"
#include <Arduino.h>
#include <DS3231.h>   // install Ds3231 by Andrew Wickert
///////////////////////////
#include <Wire.h>

DS3231 rtc;

RtcDs3231::RtcDs3231()  // Constructor
{ 

}
//__________________________________________________________________________________________________________________________________________________________________
void RtcDs3231::init(void)
{
    
    Wire.begin();
    
     // Uncomment the following line to set date/time initially, then comment it again after uploading once.
  // rtc.setYear(25); rtc.setMonth(3); rtc.setDate(22); rtc.setHour(20); rtc.setMinute(55); rtc.setSecond(0);
}
//_________________________________________________________________________________________________________________________________________________________________
void RtcDs3231::display(void)
{
  bool century = false;
  bool h12 = false;
  bool PM = false;

  int year = rtc.getYear();
  int month = rtc.getMonth(century);
  int date = rtc.getDate();
  int hour = rtc.getHour(h12, PM); // 24-hour format if h12 is false
  int minute = rtc.getMinute();
  int second = rtc.getSecond();

  // Display Date
  Serial.print("Date: ");
  if (date < 10) Serial.print("0");
  Serial.print(date);
  Serial.print("/");
  if (month < 10) Serial.print("0");
  Serial.print(month);
  Serial.print("/");
  Serial.print(year);

  // Display Time
  Serial.print("   Time: ");
  if (hour < 10) Serial.print("0");
  Serial.print(hour);
  Serial.print(":");
  if (minute < 10) Serial.print("0");
  Serial.print(minute);
  Serial.print(":");
  if (second < 10) Serial.print("0");
  Serial.println(second);
}
//_________________________________________________________________________________________________________________________________________________________________

