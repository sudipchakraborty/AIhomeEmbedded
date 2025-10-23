#include <Arduino.h>
#include "IRcut.h"
#include "FND.h"
#include "DEBUG.h"
#include "ANALOG.h"
#include "button.h"
#include "LED.h"
#include "RELAY.h"
#include "StatusBlink.h"
#include "Time.h"
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
Time timer;
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
  timer.set_time(5000);
}
//_____________________________________________________________________________________________________________________________________________________________________
  void ircut::FSM_Handler(void)
  {
      stbl.blink();
      CheckTimeOut();
      Sensor_Read();
      Check_Sensor();
      LoadTrigger(); 
    }
//_____________________________________________________________________________________________________________________________________________________________________
/**
 * @brief this function clear the event array. it set all four to zero
 * @param void
 * @return void
 */
void ircut::event_clear(void){
   myIRCut.event_count=1;
   myIRCut.event_val=0;
   myIRCut.v_delay_reg=0;
   Sensor_Read();
   myIRCut.sensor_state_backup=myIRCut.sensor_state_current;
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
/**
 * @brief this function clear the event array. it set all four to zero
 * @param void
 * @return void
 */
  void ircut::CheckTimeOut(void)
  {
    if(myIRCut.event_val !=0)
      {  
        timer.time_start();
        if(timer.timeOut())
        {
            dbg.print("Time Out occured");
            myIRCut.event_clear();
            timer.time_start();
            dbg.print("============================");
        }
        else{
        }
      }
      else{
        timer.time_reset();
      }
  }
//_____________________________________________________________________________________________________________________________________________________________________
/**
 * @brief this function clear the event array. it set all four to zero
 * @param void
 * @return void
 */
  void ircut::LoadTrigger(void)
  {
      if(myIRCut.event_val==29)
      {
        bulb.on();
        myIRCut.event_clear();
        return;
      }
      if(myIRCut.event_val==25)
      {
        bulb.off();
         myIRCut.event_clear();
         
         return;
      }
  }
//_____________________________________________________________________________________________________________________________________________________________________
/**
 * @brief this function clear the event array. it set all four to zero
 * @param void
 * @return void
 */
  void ircut::Check_Sensor(void)
  {
    if(myIRCut.sensor_state_backup==myIRCut.sensor_state_current) return;
   
    byte prev,curr;
    prev=myIRCut.sensor_state_backup  & 0x01;
    curr=myIRCut.sensor_state_current & 0x01;
    if(prev !=curr)
    {
        if(curr==0x01)  myIRCut.event_val += (myIRCut.event_count*1);
        if(curr==0x00)  myIRCut.event_val += (myIRCut.event_count*2);
    }
    ///////////////
    prev=myIRCut.sensor_state_backup  & 0x02;
    curr=myIRCut.sensor_state_current & 0x02;
    if(prev !=curr)
    {
        if(curr==0x02)  myIRCut.event_val += (myIRCut.event_count*3);
        if(curr==0x00)  myIRCut.event_val += (myIRCut.event_count*4);
    }     
    myIRCut.event_count++;

     myIRCut.sensor_state_backup=myIRCut.sensor_state_current;
     Serial.print("event_count=");    Serial.println(myIRCut.event_count);
     Serial.print("event_val=");      Serial.println(myIRCut.event_val);
  }
//_____________________________________________________________________________________________________________________________________________________________________
