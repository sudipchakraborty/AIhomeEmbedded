#include <Arduino.h>
#include "IRcut.h"
#include "RELAY.h"
#include "button.h"
#include "LED.h"
#include "DEBUG.h"
#include "StatusBlink.h"
#include "Time.h"
//////////////////////
debug   dbg(9600);

button ldr_inside(10);
button ldr_outside(9);

led led_inside(12,LOW);
led led_Outside(11,LOW);

relay rly_inside(2);
relay rly_outside(3);

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
  ldr_inside.begin();
  led_Outside.begin();
  led_inside.begin();
  led_inside.begin();
  stbl.init(13,5000);
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
 * @brief this function read the LDR sensor status from the controller port. the status
 * is available inside  sensor_state_current registor.
 * @param void
 * @return void
 */
  void ircut::Sensor_Read(void){
      myIRCut.sensor_state_current=0x00;
      if(ldr_outside.triggered()) 
      {
        myIRCut.sensor_state_current |=0x01;
        led_Outside.on();
      }
      else
      {
        led_Outside.off();
      }
      ///////////////////////////
      if(ldr_inside.triggered()) 
      {
        myIRCut.sensor_state_current |=0x02; 
        led_inside.on();
      }
      else{
        led_inside.off();
      }
}
//_____________________________________________________________________________________________________________________________________________________________________
/**
 * @brief this fnction compare the sensor status between previous and current status register.
 * @param void
 * @return void
 */
  void ircut::Check_Sensor(void)
  {
    if(myIRCut.sensor_state_backup==myIRCut.sensor_state_current) return;
   
    byte prev,curr;
    prev=myIRCut.sensor_state_backup  & 0x01;   // 0x01= LDR outside
    curr=myIRCut.sensor_state_current & 0x01;
    if(prev !=curr)
    {
        if(curr==0x01) 
        {
          myIRCut.event_val += (myIRCut.event_count*1);
           Serial.println("LDR outside triggered..");   
        }
        if(curr==0x00)  
        {
            myIRCut.event_val += (myIRCut.event_count*2);
            Serial.println("LDR outside Released.."); 
        }
    }
    ///////////////
    prev=myIRCut.sensor_state_backup  & 0x02;   // 0x02=LDR inside
    curr=myIRCut.sensor_state_current & 0x02;
    if(prev !=curr)
    {
        if(curr==0x02)  
        {
          myIRCut.event_val += (myIRCut.event_count*3);
           Serial.println("LDR Inside triggered.."); 
        }
        if(curr==0x00)  
        {
          myIRCut.event_val += (myIRCut.event_count*4);
           Serial.println("LDR inside  released.."); 
        }
    }     
    myIRCut.event_count++;

    myIRCut.sensor_state_backup=myIRCut.sensor_state_current;
    //  Serial.print("event_count=");    Serial.println(myIRCut.event_count);
    //  Serial.print("event_val=");      Serial.println(myIRCut.event_val);
  }
//_____________________________________________________________________________________________________________________________________________________________________
/**
 * @brief this function monitor the status register. if the sensor event status register is healthy
 * means 29 then trigger the load on and if the value is 25 then load make  off.
 * @param void
 * @return void
 */
  void ircut::LoadTrigger(void)
  {
      if(myIRCut.event_val==29)
      {
        Serial.println("Got Healthy status=29..Triggering the load on");
        rly_inside.on();
        rly_outside.on();
        myIRCut.event_clear();
        return;
      }
      if(myIRCut.event_val==25)
      {
        Serial.println("Got Healthy status=25..Triggering the load off");
          rly_inside.off();
          rly_outside.off();
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
