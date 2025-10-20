#include <Arduino.h>
#include "IRcut.h"
#include "FND.h"
#include "DEBUG.h"
#include "ANALOG.h"
#include "button.h"
#include "LED.h"
///////////////////////

//////////////////////
debug   dbg(9600);
button  ir_inside(13);
button  ir_outside(12);

led led_in(PD7);
led led_out(PD6);

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

  st = ircut::start;

  DDRD=0xff;

  pinMode(7,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(2,OUTPUT);

  digitalWrite(7, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(5, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(2, HIGH);


}
//_____________________________________________________________________________________________________________________________________________________________________
  void ircut::FSM_Handler(void){

digitalWrite(PD7, HIGH);
 led_in.flash();
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
        led_in.flash();
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



