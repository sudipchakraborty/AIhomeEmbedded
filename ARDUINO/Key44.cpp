#include "Key44.h"
#include <Arduino.h>
#include <Keypad.h>  // Install Keypad by Mark Stanley, Alexander Brevig
///////////////////////////

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {23, 25, 27, 29}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {31, 33, 35, 37}; //connect to the column pinouts of the keypad


//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);



Key44::Key44()  // Constructor
{   
}
//__________________________________________________________________________________________________________________________________________________________________
void Key44::init(void)
{
    
}
//__________________________________________________________________________________________________________________________________________________________________
bool Key44::pressed(void)
{
  char k = customKeypad.getKey();
  
  if(!k) 
  {
    return false;
  }
  else
  {
    code=k;
    return true;
  }
}
//__________________________________________________________________________________________________________________________________________________________________
char Key44::get(void)
{
  char customKey = customKeypad.getKey();
  return customKey;
  
  
}

//__________________________________________________________________________________________________________________________________________________________________