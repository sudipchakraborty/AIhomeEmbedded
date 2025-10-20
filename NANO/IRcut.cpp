#include <Arduino.h>
#include "IRcut.h"
#include "FND.h"
#include "DEBUG.h"
#include "ANALOG.h"
#include "button.h"
#include "LED.h"
#include "RELAY.h"
#include "StatusBlink.h"
///////////////////////

//////////////////////
debug   dbg(9600);

button  ir_inside(12);
button  ir_outside(13);

led led_in(11);
led led_out(10);

relay bulb(9);

StatusBlink stbl;

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
  ir_inside.begin();
  ir_outside.begin();
  led_in.begin();
  led_out.begin();
  bulb.begin();
  stbl.init(8,100000);

  st = ircut::start;
}
//_____________________________________________________________________________________________________________________________________________________________________
  void ircut::FSM_Handler(void){

    
 stbl.blink();

    switch (st) 
    {
      case ircut::start:
        dbg.show("the system is starting....");
        st=ircut::wait_for_any_trigger;
      break;
      ////////////////////
      case ircut::wait_for_any_trigger:
        if(ir_inside.triggered()){
          dbg.show("ir inside button triggered");
          led_in.flash();
          st=ircut::wait_for_outside_trigger;
        }

        if(ir_outside.triggered()){
          dbg.show("ir outside button triggered");
          led_out.flash();
          st=ircut::wait_for_inside_trigger;
        }
    break;
    ///////////////////
    case ircut::wait_for_outside_trigger:


    break;
    ///////////////////
     case ircut::wait_for_inside_trigger:
      if(ir_inside.triggered()){
          dbg.show("ir inside button triggered");
          led_in.flash();
          bulb.on();
          // st=ircut::wait_for_outside_trigger;
        }


    break;
    ///////////////////
    case ircut::status_send_log:


    break;
    ///////////////////
    default:
    break;
    ////////////////////
    }

  }
//_____________________________________________________________________________________________________________________________________________________________________



