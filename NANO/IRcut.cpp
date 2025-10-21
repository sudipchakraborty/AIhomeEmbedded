#include <Arduino.h>
#include "IRcut.h"
#include "FND.h"
#include "DEBUG.h"
#include "ANALOG.h"
#include "button.h"
#include "LED.h"
#include "RELAY.h"
#include "StatusBlink.h"
#include "TimeModule.h"
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

TimeModule timer;
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
  myIRCut.event_clear();


  int values[] = {10, 20, 30, 40, 50};
  ircut::printArray(values, 5);
}
//_____________________________________________________________________________________________________________________________________________________________________
  void ircut::FSM_Handler(void){
   
    stbl.blink();
    Sensor_Read();

    // timer.set_time(5000);  // 5 seconds timeout
    // timer.time_start();
    //   if (timer.timeOut()) {
    //     Serial.println("Timeout occurred!");
    //     timer.time_start(); // restart timer

    // if(myIRCut.ptr_event!=0)
    // {
    //   if(timeOut()){
    //     reset_events();
    //   }
    // }
    /////////////////
    // if(myIRCut.ptr_event==4)
    // {
    //       if((myIRCut.event[0]==0x01) && (myIRCut.event[0]==0x04) && (myIRCut.event[0]==0x04) && (myIRCut.event[0]==0x04)) 
    //       { // valid entry
    //            dbg.show("both release..bulb on.. going in idle state..");
    //            bulb.on();
    //       }
    //       if((myIRCut.event[0]==0x01) && (myIRCut.event[0]==0x04) && (myIRCut.event[0]==0x04) && (myIRCut.event[0]==0x04)) 
    //       { // valid exit
    //            dbg.show("both release..bulb on.. going in idle state..");
    //            bulb.off();
    //       }
    //       reset_events();
    // }
    // ///////////
    // if(myIRCut.sensor_state_backup==myIRCut.sensor_state_current) return;

    // switch (myIRCut.sensor_state_backup) 
    // {
    //   case 0x00:
    //     if(myIRCut.sensor_state_current==0x01)   myIRCut.event[myIRCut.ptr_event]=outside_trig;  //out sensor trig
    //     if(myIRCut.sensor_state_current==0x10)   myIRCut.event[myIRCut.ptr_event]=in_trig;  // inside trigger
    //     if(myIRCut.sensor_state_current==0x11)   myIRCut.event[myIRCut.ptr_event]=both_trig;    
    //     myIRCut.ptr_event++;
    //   break;
    //   ///////////
    //   case 0x01:
    //     if(myIRCut.sensor_state_current==0x00)   myIRCut.event[myIRCut.ptr_event]=outside_trig;  //out sensor trig
    //     if(myIRCut.sensor_state_current==0x10)   myIRCut.event[myIRCut.ptr_event]=in_trig;  // inside trigger
    //     if(myIRCut.sensor_state_current==0x11)   myIRCut.event[myIRCut.ptr_event]=both_trig;    
    //     myIRCut.ptr_event++;
    //   break;
    //   //////////
    //   case 0x10;
    //     if(myIRCut.sensor_state_current==0x00)   myIRCut.event[myIRCut.ptr_event]=outside_trig;  //out sensor trig
    //     if(myIRCut.sensor_state_current==0x01)   myIRCut.event[myIRCut.ptr_event]=in_trig;  // inside trigger
    //     if(myIRCut.sensor_state_current==0x11)   myIRCut.event[myIRCut.ptr_event]=both_trig;    
    //     myIRCut.ptr_event++;
    //   break;
    //   /////////
    //   case 0x11:
    //     if(myIRCut.sensor_state_current==0x00)   myIRCut.event[myIRCut.ptr_event]=outside_trig;  //out sensor trig
    //     if(myIRCut.sensor_state_current==0x10)   myIRCut.event[myIRCut.ptr_event]=in_trig;  // inside trigger
    //     if(myIRCut.sensor_state_current==0x01)   myIRCut.event[myIRCut.ptr_event]=both_trig;    
    //     myIRCut.ptr_event++;
    //   break;
    //   /////////
    //   default:
    //   break;
    //   ////////
    // }






  // myIRCut.sensor_state_backup =myIRCut.sensor_state_current;
  //   }

  //   switch (st) 
  //   {
  //     case ircut::start:
  //       dbg.print("the system is starting....");
  //       st=ircut::idle;
  //     break;
  //     ////////////////////
  //     case ircut::idle:
  //       if(ir_outside.triggered())  
  //       {
  //         myIRCut.event[myIRCut.ptr_event]=outside_trig;
  //         myIRCut.ptr_event++;
  //       }
  //       //////
  //       if(ir_inside.triggered())  
  //       {
  //         myIRCut.event[myIRCut.ptr_event]=in_trig;
  //         myIRCut.ptr_event++;
  //       }
  //     case ircut::idle2:
  //       if(!ir_outside.triggered())  
  //       {
  //         myIRCut.event[myIRCut.ptr_event]=out_release;
  //         myIRCut.ptr_event++;
  //       }
  //       //////
  //       if(ir_inside.triggered())  
  //       {
  //         myIRCut.event[myIRCut.ptr_event]=in_trig;
  //         myIRCut.ptr_event++;
  //       }




// #define     1
// #define      2
// #define          4
// #define in_release      8

        // {
        //   dbg.show("------------------------------------------");
        //   dbg.show("Out triggered first. wait for both on..");
        //   led_out.flash();
        //   st=ircut::check_for_valid_IN;
        // }
        // ///
        // if(ir_inside.triggered()){
        //   dbg.show("------------------------------------------");
        //   dbg.show("in triggered first. wait for both on..");
        //   led_in.flash();
        //   st=ircut::check_for_valid_out;
        // }
    // break;
    // ///////////////////
    // case check_for_valid_IN:
    //   if(ir_outside.triggered() && ir_inside.triggered())
    //   {
    //      dbg.show("both triggerd.. wait for release");
    //      st=ircut::validate_IN;
    //   }
    // break;
    // //////////////////////
    // case validate_IN:
    //   if(!ir_outside.triggered() && !ir_inside.triggered())
    //   {
    //      dbg.show("both release..bulb on.. going in idle state..");
    //      bulb.on();
    //      st=ircut::idle;
    //   }
    // break;
    // //////////////////////
    //  case check_for_valid_out:
    //   if(ir_outside.triggered() && ir_inside.triggered())
    //   {
    //        dbg.show("both triggerd.. wait for release");
    //       st=ircut::validate_Out;
    //   }
    // break;
    // ///////////////////////
    // case validate_Out:
    //   if(!ir_outside.triggered() && !ir_inside.triggered())
    //   {
    //      dbg.show("both release..bulb off.. going in idle state..");
    //      bulb.off();
    //      st=ircut::idle;
    //   }
    // break;
    // ///////////////////////
    // default:
    // break;
    // ////////////////////
    // }

  }
//_____________________________________________________________________________________________________________________________________________________________________
/**
 * @brief this function clear the event array. it set all four to zero
 * @param void
 * @return void
 */
void ircut::event_clear(void){
  myIRCut.event[0]=0;
  myIRCut.event[1]=0;
  myIRCut.event[2]=0;
  myIRCut.event[3]=0;
  myIRCut.ptr_event=0;
  myIRCut.sensor_state_backup=0x00;
}
//_____________________________________________________________________________________________________________________________________________________________________
/**
 * @brief this function clear the event array. it set all four to zero
 * @param void
 * @return void
 */
  void ircut::Sensor_Read(void){
      myIRCut.sensor_state_current=0x00;
      if(ir_outside.triggered()) myIRCut.sensor_state_current |=0x01;
      if(ir_inside.triggered())  myIRCut.sensor_state_current |=0x02; 
}
//_____________________________________________________________________________________________________________________________________________________________________
template <typename T>
void ircut:: printArray(const T arr[], size_t size) {
    Serial.print("[ ");
    for (size_t i = 0; i < size; i++) {
        Serial.print(arr[i]);
        if (i < size - 1) Serial.print(", ");
    }
    Serial.println(" ]");
}


