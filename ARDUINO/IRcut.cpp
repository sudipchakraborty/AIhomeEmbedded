#include <Arduino.h>
#include "IRcut.h"
#include "FND.h"
#include "DEBUG.h"
#include "ANALOG.h"
#include "button.h"
///////////////////////

//////////////////////
fnd display(13, 12, 11);
debug dbg(9600);
analog temp(A0);
button ir_inside(13);
button ir_outside(12);

 
ircut myIRCut;
ircut::state st;
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
  dbg.begin();
  display.begin();
  ir_inside.begin();
  ir_outside.begin();
  st = ircut::start;
}
//_____________________________________________________________________________________________________________________________________________________________________
  void ircut::FSM_Handler(void){

    switch (st) {
    case ircut::start:
      dbg.show("the system is starting....");
      st=ircut::wait_for_trigger;
    break;
    ////////////////////
    case ircut::wait_for_trigger:
      //  dbg.show("the system is wait_for_trigger....");
      if(ir_inside.triggered()){
        dbg.show("ir inside button triggered");
      }

      if(ir_outside.triggered()){
        dbg.show("ir outside button triggered");
      }


      // st=ircut::wait_for_release;
    break;
    ///////////////////
    case ircut::wait_for_release:


    break;
    ///////////////////
    case ircut::status_send_log:


    break;
    ///////////////////
    default:
    break;
    ////////////////////
    }



    // int val=temp.GetValue();
    // dbg.show(val);
    // delay(100); // Update every 100ms
  }
//_____________________________________________________________________________________________________________________________________________________________________



