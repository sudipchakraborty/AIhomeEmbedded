#include "LedRGB.h"
#include <Arduino.h>
///////////////////////////
LedRGB::LedRGB()  // Constructor
{   
}
//__________________________________________________________________________________________________________________________________________________________________
void LedRGB::init(void)
{
    count_Reg=0;
    compare_val=0; 
}
//__________________________________________________________________________________________________________________________________________________________________
 void LedRGB::set(long val)
{
    compare_val=val;  
    count_Reg=0;
}
//__________________________________________________________________________________________________________________________________________________________________
bool LedRGB::over(void)
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






// //adafruit Adafruit_NeoPixel
// #include <Adafruit_NeoPixel.h>

// // Pin connected to the DIN of the LED strip
// #define LED_PIN 6

// // Number of LEDs in the strip
// #define NUM_LEDS 4

// // Create a NeoPixel object
// Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

// void setup() {
//   strip.begin();      // Initialize the LED strip
//   strip.show();       // Turn off all LEDs at the start
//   strip.setBrightness(50); // Set brightness (0-255)
// }

// void loop() {
//   // Example effects
//   colorWipe(strip.Color(255, 0, 0), 50); // Red
//   colorWipe(strip.Color(0, 255, 0), 50); // Green
//   colorWipe(strip.Color(0, 0, 255), 50); // Blue
//   rainbow(10);                           // Rainbow effect
// }

// // Fill the strip with a single color
// void colorWipe(uint32_t color, int wait) {
//   for (int i = 0; i < strip.numPixels(); i++) {
//     strip.setPixelColor(i, color); // Set the color of pixel i
//     strip.show();                 // Update the strip to show the change
//     delay(wait);                  // Wait for the next LED
//   }
// }

// // Create a rainbow effect
// void rainbow(int wait) {
//   for (int j = 0; j < 256; j++) { // Cycle all colors
//     for (int i = 0; i < strip.numPixels(); i++) {
//       strip.setPixelColor(i, wheel((i + j) & 255));
//     }
//     strip.show();
//     delay(wait);
//   }
// }

// // Generate rainbow colors across 0-255
// uint32_t wheel(byte position) {
//   position = 255 - position;
//   if (position < 85) {
//     return strip.Color(255 - position * 3, 0, position * 3);
//   } else if (position < 170) {
//     position -= 85;
//     return strip.Color(0, position * 3, 255 - position * 3);
//   } else {
//     position -= 170;
//     return strip.Color(position * 3, 255 - position * 3, 0);
//   }
// }
























