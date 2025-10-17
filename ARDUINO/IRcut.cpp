#include <Arduino.h>
#include "IRcut.h"
#include "FND.h"
#include "DEBUG.h"
#include "ANALOG.h"
///////////////////////

//////////////////////
fnd display(13, 12, 11);
debug dbg(9600);
analog temp(A0);


//_____________________________________________________________________________________________________________________________________________________________________

/**
 * @brief Brief description of the function/class
 * @param param1 Description of first parameter
 * @param param2 Description of second parameter
 * @return Description of return value
 */
ircut::ircut(){
  
}
//_____________________________________________________________________________________________________________________________________________________________________
/**
 * @brief Brief description of the function/class
 * @param param1 Description of first parameter
 * @param param2 Description of second parameter
 * @return Description of return value
 */
void ircut::begin(void){
      // temp.begin();
  dbg.begin();
  display.begin();
}
//_____________________________________________________________________________________________________________________________________________________________________
  void ircut::FSM_Handler(void){
    int val=temp.GetValue();
    dbg.show(val);
    delay(100); // Update every 100ms
  }
//_____________________________________________________________________________________________________________________________________________________________________



