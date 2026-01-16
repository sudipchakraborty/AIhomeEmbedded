#include <Arduino.h>
#include "IRcut.h"
#include "RELAY.h"
#include "button.h"
#include "LED.h"
#include "DEBUG.h"
#include "StatusBlink.h"
#include "Time.h"
#include "global_var.h"
#include "EventsSEQ.h"
//////////////////////

debug   dbg(19200);

button IR_inside(10,1);
button IR_outside(9,1);

// button IR_inside(10,0);
// button IR_outside(9,0);

led led_inside(12,LOW);
led led_Outside(11,LOW);

relay rly_inside(2);
relay rly_outside(3);

StatusBlink stbl;
ircut myIRCut;
ircut::state st;

EventsSEQ myEventsSEQ;

Time timer;

  // Burst timing (milliseconds)
#include <avr/interrupt.h>

#define IR_PIN 3   // OC2B (Arduino Nano)

#define IR_ON_MS   5
#define IR_OFF_MS  15

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
  dbg.print("\n\n\r///////////////<NEW SEASON>/////////////////////////");
  IR_inside.begin();
  led_Outside.begin();
  
  led_inside.begin();
  led_inside.begin();

  rly_inside.begin();
  rly_outside.begin();

  stbl.init(13,5000);
  st = ircut::start;
  myIRCut.event_clear();
  timer.set_time(5000);

  myEventsSEQ.begin();

  device_self_test();
  dbg.print("Device Initialized Completed...");
  dbg.print("IR Cut Controller Started...");
  dbg.print("-----------------------------------------------");

  // PWM_setup();
  // setup_timer2_38kHz();
  // setup_timer1_burst();
  // sei(); // enable global interrupts

}
//_____________________________________________________________________________________________________________________________________________________________________
  void ircut::FSM_Handler(void)
  {
    if(Sensor_Health==Good)
    {
      
      Sensor_Read();

      if(myIRCut.sensor_state_backup!=myIRCut.sensor_state_current) 
      {
        Check_Sensor2();
        String s=myEventsSEQ.get_buffer_as_string();
        dbg.print("Event Buffer: "+s);

        // LoadTrigger(); 
        stbl.blink();
      }
    }
    else{
      sensor_health_check();
      if(Sensor_Health==Good)
      {
        dbg.print("Sensor Health OK..resuming normal operation");
        delay(500);
      }
      else
        dbg.print("Sensor Health BAD..check the sensors");
        delay(500);
    }
          CheckTimeOut();
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
   
      if(IR_outside.triggered()) 
      {
        myIRCut.sensor_state_current|=0x01;
        led_Outside.on();
      }
      else
      {
        myIRCut.sensor_state_current &=0xFE;
        led_Outside.off();
      }
      ///////////////////////////
      if(IR_inside.triggered()) 
      {
        myIRCut.sensor_state_current |=0x02; 
        led_inside.on();
      }
      else{
        myIRCut.sensor_state_current &=0xFD;
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
          dbg.print("LDR outside triggered..");
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
          dbg.print("LDR Inside triggered.."); 
        }
        if(curr==0x00)  
        {
          myIRCut.event_val += (myIRCut.event_count*4);
          dbg.print("LDR inside  released.."); 
        }
    }     
    myIRCut.event_count++;

    myIRCut.sensor_state_backup=myIRCut.sensor_state_current;
    // Serial.print("event_count=");    Serial.println(myIRCut.event_count);
    // Serial.print("event_val=");      Serial.println(myIRCut.event_val);
  }
//_____________________________________________________________________________________________________________________________________________________________________
/**
 * @brief this fnction compare the sensor status between previous and current status register.
 * @param void
 * @return void
 */
  void ircut::Check_Sensor2(void)
  {
    byte prev,curr;
    prev=myIRCut.sensor_state_backup  & 0x01;   // 0x01= LDR outside
    curr=myIRCut.sensor_state_current & 0x01;
    if(prev !=curr)
    {
        if(curr==0x01) 
        {
          myEventsSEQ.push(Out_ON); 
          dbg.print("LDR outside triggered..");
        }
        if(curr==0x00)  
        {
            myEventsSEQ.push(Out_OFF);
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
          myEventsSEQ.push(In_ON);
          dbg.print("LDR Inside triggered.."); 
        }
        if(curr==0x00)  
        {
          myEventsSEQ.push(In_OFF);
          dbg.print("LDR inside  released.."); 
        }
    }     
    myIRCut.sensor_state_backup=myIRCut.sensor_state_current;
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
    if(myEventsSEQ.index !=0)
      {  
        timer.time_start();
        if(timer.timeOut())
        {
            dbg.print("Time Out occured");
            // myIRCut.event_clear();
            myEventsSEQ.buffer_reset();
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
void ircut:: device_self_test(void)
{
  /**
 * @brief this is the device self test function. it will test all the major components of the device
 * @param void
 * @return void
 */
    //////////////////
    dbg.print("Device Self Test Started...");
     delay(2000);

      sensor_health_check();
      ////////////////////////////
      dbg.print("Inside Relay Test...");
      rly_inside.on();
      delay(500);
      rly_inside.off();
      delay(500);
      ///////////////////
      dbg.print("Outside Relay Test...");
      rly_outside.on();
      delay(500);
      rly_outside.off();
      delay(500);
    ///////////////////
}
//_____________________________________________________________________________________________________________________________________________________________________
 ///////////////////
 void ircut:: sensor_health_check(void){
  /**
 * @brief  this function check the health of the IR sensors
 * @param void
 * @return void
 */
  if(IR_outside.triggered()) 
      {  
        dbg.print("Outside IR Sensor Error or IR light not detected...");
        led_Outside.off();
        OutSide_sensor_error=true;
      }
      else
      {
        dbg.print("Outside IR Sensor OK and sensing the IR light...");
        led_Outside.on();
        OutSide_sensor_error=false;
      }
      delay(500);
      ///////////////////////////
      if(IR_inside.triggered()) 
      {
        dbg.print("Inside IR Sensor Error or IR light not detected...");
        led_inside.off();
        InSide_sensor_error=true;
      }
      else{
        dbg.print("Inside IR Sensor OK and sensing the IR light...");
        led_inside.on();
        InSide_sensor_error=false;
      }
      delay(500);
      ////////////////////////////
      dbg.print("Evaluating Sensor Health...");
      if (OutSide_sensor_error || InSide_sensor_error)
      {
        Sensor_Health=false;
        dbg.print("Sensor Health: BAD");
      }
      else{
        Sensor_Health=true;
        dbg.print("Sensor Health: OK");
      }
      delay(500);
    }
//_____________________________________________________________________________________________________________________________________________________________________




// Continuous High-Power IR Burst (38kHz Background PWM)
// Hardware: Arduino Nano, 2N2222, IR LED
// Wiring: Base of Transistor connected to Pin D3 via 220 ohm resistor

// const byte IR_PIN = 3; // Hardwired to Timer 2 Output B

void ircut::PWM_setup() {

   pinMode(IR_PIN, OUTPUT);

  // Stop Timer2
  TCCR2A = 0;
  TCCR2B = 0;

  // Fast PWM, TOP = OCR2A
  TCCR2A = _BV(WGM21) | _BV(WGM20);
  TCCR2B = _BV(WGM22) | _BV(CS21); // Prescaler = 8

  // 38 kHz
  OCR2A = 51;
  OCR2B = 17; // ~33% duty (better for IR LED & transistor)

  // IMPORTANT:
  // DO NOT enable COM2B1 here (PWM output disabled initially)




  // // 1. Set the pin to Output
  // pinMode(IR_PIN, OUTPUT);

  // // 2. Configure Timer 2 for 38kHz PWM (Fast PWM Mode)
  // // This interacts directly with the microcontroller hardware.
  // // Once set, the pin pulses automatically without stopping.
  
  // // Clear Timer Control Registers
  // TCCR2A = 0;
  // TCCR2B = 0;

  // // TCCR2A settings:
  // // COM2B1 = 1: Clear OC2B on Compare Match (non-inverting mode)
  // // WGM21 + WGM20 = 1: Fast PWM Mode
  // TCCR2A = _BV(COM2B1) | _BV(WGM21) | _BV(WGM20);

  // // TCCR2B settings:
  // // WGM22 = 1: Fast PWM Mode (continued)
  // // CS21  = 1: Prescaler = 8 (16MHz / 8 = 2MHz counter)
  // TCCR2B = _BV(WGM22) | _BV(CS21);

  // // OCR2A (Top Limit): Determines Frequency
  // // Formula: (16MHz / (Prescaler * TargetFreq)) - 1
  // // (16,000,000 / (8 * 38,000)) - 1 = 51.6 -> 52
  // OCR2A = 51; 

  // // OCR2B (Duty Cycle): Determines brightness/power
  // // 50% of OCR2A is usually best for IR data, but for raw power:
  // // 26 = 50% Duty Cycle
  // OCR2B = 17; 

  // // --- PWM IS NOW RUNNING ON PIN 3 ---
  
  // // Optional: Start Serial to prove the loop is free
  // // Serial.begin(9600);




  /////////////////

}

// void ircut::PWM_burst_task() {
//   static unsigned long lastToggle = 0;
//   static bool pwmEnabled = false;

//   unsigned long now = millis();

//   if (pwmEnabled) {
//     // PWM currently ON
//     if (now - lastToggle >= IR_BURST_ON_MS) {
//       // Disable PWM output (carrier OFF)
//       TCCR2A &= ~_BV(COM2B1);
//       digitalWrite(IR_PIN, LOW); // ensure clean LOW
//       pwmEnabled = false;
//       lastToggle = now;
//     }
//   } else {
//     // PWM currently OFF
//     if (now - lastToggle >= IR_BURST_OFF_MS) {
//       // Enable PWM output (carrier ON)
//       TCCR2A |= _BV(COM2B1); // connect OC2B to timer
//       pwmEnabled = true;
//       lastToggle = now;
//     }
//   }
// }


void ircut::setup_timer2_38kHz(void) {
  pinMode(IR_PIN, OUTPUT);

  TCCR2A = 0;
  TCCR2B = 0;

  // Fast PWM, TOP = OCR2A
  TCCR2A = _BV(WGM21) | _BV(WGM20);
  TCCR2B = _BV(WGM22) | _BV(CS21); // prescaler = 8

  OCR2A = 51;   // 38 kHz
  OCR2B = 17;   // ~33% duty

  // PWM output disabled initially
  TCCR2A &= ~_BV(COM2B1);
}


void ircut::setup_timer1_burst(void) {
  TCCR1A = 0;
  TCCR1B = 0;

  // CTC mode
  TCCR1B |= _BV(WGM12);

  // Prescaler = 64 → 16MHz / 64 = 250 kHz
  TCCR1B |= _BV(CS11) | _BV(CS10);

  // Start with ON duration
  OCR1A = IR_ON_MS * 250 - 1;

  TIMSK1 |= _BV(OCIE1A); // enable compare interrupt
}


ISR(TIMER1_COMPA_vect) {
  static bool ir_on = false;

  if (ir_on) {
    // Turn IR OFF
    TCCR2A &= ~_BV(COM2B1);  // disconnect OC2B
    digitalWrite(IR_PIN, LOW);

    OCR1A = IR_OFF_MS * 250 - 1;
    ir_on = false;
  } else {
    // Turn IR ON
    TCCR2A |= _BV(COM2B1);   // connect OC2B

    OCR1A = IR_ON_MS * 250 - 1;
    ir_on = true;
  }
}
//_____________________________________________________________________________________________________________________________________________________________________


void ircut::setup_timer2_38kHz(void) {
  pinMode(IR_PIN, OUTPUT);

  TCCR2A = 0;
  TCCR2B = 0;

  // Fast PWM, TOP = OCR2A
  TCCR2A = _BV(WGM21) | _BV(WGM20);
  TCCR2B = _BV(WGM22) | _BV(CS21); // prescaler = 8

  OCR2A = 51;   // 38 kHz
  OCR2B = 17;   // ~33% duty

  // PWM output disabled initially
  TCCR2A &= ~_BV(COM2B1);
}

//_____________________________________________________________________________________________________________________________________________________________________
void ircut::event_detect(void) {
  
}
//_____________________________________________________________________________________________________________________________________________________________________

// 1324 in
// 3142 out