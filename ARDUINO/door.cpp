#include "door.h"
#include <Arduino.h>
#include "button.h"
#include "buzzer.h"
#include "PWM.h"
#include "virtualCounter.h"
#include "timer1.h"
////////////////////////
#include "StatusBlink.h"

#include "CommandParser.h"
#include <ArduinoJson.h>
#include "Arduino.h"
///////////////////////
button btn_trig;
button btn_home;
button btn_outSide;

button sw_door_open;
buzzer bzr;
PWM motor;
virtualCounter count;
extern timer1 t1;

int state_count=0;

#define Emergency_SW_PIN 3   // Switch 1 connected to pin 3
#define Close_Sensor_PIN 35 //19  // Switch 2 connected to pin 19
#define Calling_Bell_Trigger  37
#define pin_sw_outside        39
#define Open_Sensor_PIN 20  // Switch 3 connected to pin 20

volatile bool Emergency_SW= false; // State of Switch 1
volatile bool Close_Sensor= false; // State of Switch 2
volatile bool Open_Sensor= false; // State of Switch 3
volatile  char SensorTrigger=false;

unsigned long SensorErrCount=0;


StatusBlink st;
CommandParser cmd;

String receivedDataMega = ""; // Buffer to store incoming data
/////////////////////////////////////
void EmergencySwISR() 
{
  Serial3.println("Emergency Switch ");
}
////////////////////////////////
// void CloseSensorISR() 
// {
//   motor.updateDutyCycle(0);
//   SensorTrigger=close;
//   cli(); // Disable all interrupts globally
// }
// ///////////////////////////////
// void OpenSensorISR() 
// { 
//   motor.updateDutyCycle(0);
//   SensorTrigger=open;
// }
//___________________________________________________________________________________________________________________________________________________________
door::door()
{
}
//___________________________________________________________________________________________________________________________________________________________
void door::init(void)
{
    pinMode(LED_Yellow,OUTPUT);
    digitalWrite(LED_Yellow,HIGH);
    pinMode(PIN_DIR, OUTPUT);
    pinMode(Calling_Bell_Trigger, OUTPUT); 
    digitalWrite(Calling_Bell_Trigger,HIGH);
    TestCount=0;
    bzr.init(31);
    btn_trig.init(29);
    btn_home.init(4);
    btn_outSide.init(pin_sw_outside);
    sw_door_open.init(PIN_sw_door_open);

    Waiting_Count=0;
    motor.init(2,30000);
    motor.disable();
    count.init(); 
    home_sw_status=false;
     
    pinMode(Emergency_SW_PIN, INPUT_PULLUP);
    pinMode(Close_Sensor_PIN, INPUT_PULLUP);
    pinMode(Open_Sensor_PIN, INPUT_PULLUP);

     // Attach interrupts for the switches
    // attachInterrupt(digitalPinToInterrupt(Emergency_SW_PIN), EmergencySwISR,LOW);
    // attachInterrupt(digitalPinToInterrupt(Close_Sensor_PIN), CloseSensorISR, LOW);
    // attachInterrupt(digitalPinToInterrupt(Open_Sensor_PIN), OpenSensorISR, LOW);

    t1.init(25);
    t1.target_count(5);

    FSM=FSM_Idle;
    bzr.beep();
    pinMode(LED_Green, OUTPUT);
    ////////////
    cmd.init();
    st.init(23,1000);
    Serial.begin(115200); 
    Serial3.begin(115200);
}
//___________________________________________________________________________________________________________________________________________________________
/**
 * @brief initialize function
 * @param   to set the output
  * @param   to set the blink speed
 * @return void
 */
void door::handle(void)
{
  unsigned int temp;

  // Simple_Method();
  // return;

  // if(btn_outSide.pressed())
  // {
  //   // bzr.beep();
  //   trigger_calling_bell();
  // }

  read_home_swicth();
  ////////////////////////////////////
  switch(FSM)
  {
    case FSM_Idle:
    Serial.println("I am at idle state..");
    FSM=FSM_Init;
    break;
    /////////////////////
    case FSM_Init:  
    Serial.println("FSM_Init state..");
    FSM=FSM_check_door_open;
    break;
    //////////////////
    case FSM_check_door_open:
      if(door_not_closed())
      {
         Serial.println("door_not_closed.. Going to close..");
         delay(1000);
         set_door_close();
         Serial.println(" Set Motor Direction is to be closed");
         motor.updateDutyCycle(20);
         motor.enable();
         t1.target_count(5000);
         FSM=FSM_Wait_For_Full_Close;
      }
      else
      {
         Serial.println("door closed..\r\nwait for trigger..");
         FSM=FSM_Wait_For_Trigger;
      }
    break;
    ///////////////////
    case FSM_Wait_For_Full_Close:

    if(door_closed())
    {
       motor.updateDutyCycle(0);
       Serial.println("\rdoor closed Now. Waiting for Trigger to open the door..");
       FSM=FSM_Wait_For_Trigger;
    }
    else
    {
      Serial.print("\r Waiting for door close. Target Count="); Serial.print(t1.targetVal); Serial.print(" of "); Serial.println(t1.countReg);  
    } 
    break;
    ///////////////////////////////
     case FSM_Wait_For_Trigger:

       if(btn_outSide.pressed())
  {
    // bzr.beep();
    trigger_calling_bell();
  }

      if(btn_trig.pressed() || (btn_outSide.pressed())||(Web_Command=="Open"))
      {
          Web_Command="";
          bzr.beep();
          set_door_open();
          t1.target_count(10);
          motor.updateDutyCycle(10);
          motor.enable();
          door_Activity=Door_Opening;   
          FSM=FSM_Initial_Jogg;
          Serial.println("Starting Initial Jog...");
      }
     break;
     ///////////////////
   case FSM_Initial_Jogg:
    if(t1.completed)
      {
        t1.reset();
        Serial.println("\r\nInitial Jog Completed..Start Accelerating..");
        t1.target_count(3);
        accl_count_reg=10;
        FSM=FSM_Acceleration;
      } 
      else
      {
        Serial.print("\r Initial Jig. Target Count="); Serial.print(t1.targetVal); Serial.print(" of "); Serial.println(t1.countReg);  
      }
   break;
     ///////////////////
   case FSM_Acceleration:
     if(t1.completed)
      {
        t1.reset();
        accl_count_reg++;
        Serial.print("accl_count_reg=");Serial.println(accl_count_reg);
        motor.updateDutyCycle(accl_count_reg);
        motor.enable();
        if(accl_count_reg>=40)
        {
          jog_count_reg=0;
          Serial.println("\r\nAcceleration Completed. Going to Jog Phase..");         
          t1.reset();
          t1.target_count(50);
          FSM=FSM_Jog;
        }
      }
      else
      {
        // Serial.print("\r Door acclerting... Target Count="); Serial.print(t1.targetVal); Serial.print(" of "); Serial.println(t1.countReg);  
      }

   break;
     ///////////////////
   case FSM_Jog:
   if(t1.completed)
      {
        t1.reset();
        Serial.println("\r\nJog Completed. Going to deceleration..");
        t1.target_count(3);
        accl_count_reg=40;
          // motor.updateDutyCycle(0);
          // while(1);
        FSM=FSM_Deceleration;
        
      }
   break;
     ///////////////////
   case FSM_Deceleration:
    if(t1.completed)
      {
        t1.reset();
        accl_count_reg--;
        Serial.print("Decl_count_reg=");Serial.println(accl_count_reg);
        motor.updateDutyCycle(accl_count_reg);
        motor.enable();
        if(accl_count_reg<=15)
        {
          Serial.println("\r\nDecl. Completed. Going to Jog Phase..");         
          t1.reset();
          t1.target_count(5);
          FSM=FSM_Final_Jogg;
          SensorErrCount=0;
        }
      }
   break;
     ///////////////////
   case FSM_Final_Jogg:

      if(t1.completed)
      {
        SensorErrCount++;
         //////////////////////////////////
         if(door_Activity==Door_Opening)
          {
            temp=digitalRead(PIN_sw_door_open);

            if((temp==0)||(SensorErrCount>100))
            {
                SensorErrCount=0;
                motor.updateDutyCycle(0);
                Serial.println("Sensor contacted");
                digitalWrite(LED_Yellow,LOW);
                t1.target_count(500);
                FSM=FSM_Waiting_to_Start_Close; 
                bzr_interval=1000;   
            }
          }
          /////////////////////////////////////
          else if(door_Activity==Door_Closing)
          {
             if((door_closed()) ||(SensorErrCount>100))
             {
                SensorErrCount=0;
                motor.updateDutyCycle(0);
                Serial.println("Sensor close contacted");
                FSM=FSM_Wait_For_Trigger;    
            }
          }
          else{}
          //////////////////////////////////////
          t1.reset();
      }
      /////////////////////////
    break;
    ////////////////////////
    case FSM_Waiting_to_Start_Close:

      if((t1.completed) || (btn_trig.pressed() || (btn_outSide.pressed())))
      {
          set_door_close();
          t1.target_count(10);
          motor.updateDutyCycle(10);
          motor.enable();
          door_Activity=Door_Closing;   
          FSM=FSM_Initial_Jogg;
          Serial.println("Starting Initial Jog...");
          t1.reset();
          digitalWrite(LED_Yellow,HIGH);
      } 
      else
      {
        bzr.beep(50);
        delay(bzr_interval);
        bzr_interval=bzr_interval-50;
      }  
    break;
    ///////////////////////////
    case FSM_Testing_Loop:
    //  String dist= *(cmd+1); 
    // int intValue = dist.toInt(); 
     Serial.println("Door Opening upto=6000");
    // Serial.println(String(intValue));
    test_open(5700);

    delay(3000);
  /////////////////////////
    // String dist= *(cmd+1); 
    // int intValue = dist.toInt(); 
     Serial.println("Door Closing upto=5500");
    // Serial.println(String(intValue));
    test_close(5300);

    delay(2000);

    loop_test_count--;
    Serial.print("Loop Count=");
    Serial.println(loop_test_count);

    if(loop_test_count<=0)
    {
        FSM=FSM_Idle;
        Serial.println(String("Loop Completed..."));
    }
    break;
    /////////////////////////

    defult:
    break;
  } 
}
//___________________________________________________________________________________________________________________________________________________________
/**
 * @brief Jog function
 * @param  val_inc increment value
 * @param  val_cmp compare value
 * @return true if jog completed, else false
 */
bool door::JoG_Completed(unsigned int val_inc, unsigned int val_cmp)
{
  if(count.over())
  {
      if(val_inc>=val_cmp)
      {
        Serial3.println("\r\nJog Completed");
        return true;
      }
      else
      {
        temp++;
        Serial3.print("\rJog Count=");  Serial3.print(temp);
        return false;
      }
  }
  else
  {
      return false;
  }
}
//___________________________________________________________________________________________________________________________________________________________________________________
/**
 * @brief set motor direction bit as door open
 * @param  void
 * @param  void
 * @return void
 */
void door::set_door_open(void)
{
  digitalWrite(PIN_DIR, Dir_Open);
  door_Activity=Door_Opening;
}
//___________________________________________________________________________________________________________________________________________________________________________________
/**
 * @brief set motor direction bit as door close
 * @param  void
 * @param  void
 * @return void
 */
void door::set_door_close(void)
{
  digitalWrite(PIN_DIR, Dir_Close);
  door_Activity=Door_Closing;
}
//___________________________________________________________________________________________________________________________________________________________________________________
 /**
 * @brief set motor direction bit as door close
 * @param  void
 * @param  void
 * @return void
 */
 bool door:: door_not_closed(void)
 {
    bool st=digitalRead(Close_Sensor_PIN);
    if(st !=0) return true;
    else return false;
 } 
 //___________________________________________________________________________________________________________________________________________________________________________________
 /**
 * @brief set motor direction bit as door close
 * @param  void
 * @param  void
 * @return void
 */
 bool door:: door_closed(void)
 {
     char read_count=0;
    do
    {
        bool st=digitalRead(Close_Sensor_PIN);
        if(st==1) return false;
        delay(10);
        read_count++;
    }while(read_count<10);
    return true;
 } 
 //___________________________________________________________________________________________________________________________________________________________________________________
 /**
 * @brief set motor direction bit as door close
 * @param  void
 * @param  void
 * @return void
 */
 bool door:: door_opened(void)
 {
    bool st=digitalRead(Open_Sensor_PIN);
    if(st ==0) return true;
    else return false;
 } 
 //__________________________________________________________________________________________________________________________________________________________________________________
/**
 * @brief set motor direction bit as door close
 * @param  void
 * @param  void
 * @return void
 */
void door::PrintSensorStatus(void)
{
    bool cs=digitalRead(Close_Sensor_PIN);
    Serial.print("\rCLOSE SENSOR STATUS="); 
    if(cs==0) Serial.println("CLOSED"); else  Serial.println("OPEN");

   // bool os=digitalRead(Open_Sensor_PIN);
 
}
//__________________________________________________________________________________________________________________________________________________________________________________
/**
 * @brief set motor direction bit as door close
 * @param  void
 * @param  void
 * @return void
 */
void door::test_close(unsigned int duration)
{
   set_door_close();
   t1.target_count(10);
   motor.updateDutyCycle(30);
   motor.enable();
  //  delay(2000);
  //    motor.updateDutyCycle(20);
  //      delay(1000);
  //    motor.updateDutyCycle(10);

   delay(duration);
   motor.updateDutyCycle(0);

  //  if(door_not_closed())
  //     {
  //       Serial.println("Not close");
  //     }
  //     else
  //     {
  //        Serial.println("sensor close detected");
  //          motor.updateDutyCycle(0);
  //     }

}
//__________________________________________________________________________________________________________________________________________________________________________________
/**
 * @brief set motor direction bit as door close
 * @param  void
 * @param  void
 * @return void
 */
void door::test_open(unsigned int duration)
{
   set_door_open();
   t1.target_count(10);
   motor.updateDutyCycle(30); // 20
   motor.enable();

   delay(duration);
   motor.updateDutyCycle(0);
}
//__________________________________________________________________________________________________________________________________________________________________________________
/**
 * @brief fuction to take action against user command through terminal
 * @param  void
 * @param  void
 * @return void
 */
void door::action_for_command(String *cmd)
{
  String s=*cmd;

  if(s=="f") // forward
  {
    String dist= *(cmd+1); 
    int intValue = dist.toInt(); 
    Serial.print("Motor Moving Forward  upto=");
    Serial.println(String(intValue));
  }
  /////////////////////////
   if(s=="o") // forward
  {
    String dist= *(cmd+1); 
    int intValue = dist.toInt(); 
    Serial.print("Door Opening upto=");
    Serial.println(String(intValue));
    test_open(intValue);
  }
  /////////////////////////
    if(s=="c") // forward
  {
    String dist= *(cmd+1); 
    int intValue = dist.toInt(); 
    Serial.print("Door Opening upto=");
    Serial.println(String(intValue));
    test_close(intValue);
  }
  /////////////////////////
   if(s=="l") // forward
  {
     String dist= *(cmd+1); 
     loop_test_count = dist.toInt(); 
     FSM=FSM_Testing_Loop;
  }
  /////////////////////////
  if(s=="r") // forward
  {

  }
  /////////////////////////
  if(s=="s") // start
  {

  }
  /////////////////////////
  if(s=="p") // start
  {

  }
  /////////////////////////
  if(s=="sen_st") // start
  {
       if(door_not_closed())
       {
        Serial.println("Not Closed");
       }
       else
       {
        Serial.println("Closed");
       }
  }
  /////////////////////////
   if(s=="state") // start
  {
      switch(FSM)
      {
        case  FSM_Idle: Serial.println("FSM_Idle"); break;
        case  FSM_Init: Serial.println("FSM_Init"); break;
        case  FSM_check_door_open: Serial.println("FSM_check_door_open"); break;
        case  FSM_Wait_For_Full_Close: Serial.println("FSM_Wait_For_Full_Close"); break;
        case  FSM_Wait_For_Open_Sensor_trigger: Serial.println("FSM_Wait_For_Open_Sensor_trigger"); break;
        case  FSM_Wait_For_Close_Sensor_Trigger: Serial.println("FSM_Wait_For_Close_Sensor_Trigger"); break;
        case  FSM_Wait_For_Trigger: Serial.println("FSM_Wait_For_Trigger"); break;
        case  FSM_Initial_Jogg: Serial.println("FSM_Initial_Jogg"); break;
        case  FSM_Acceleration: Serial.println("FSM_Acceleration"); break;
        case  FSM_Deceleration: Serial.println("FSM_Deceleration"); break;
        case  FSM_Final_Jogg: Serial.println("FSM_Final_Jogg"); break;
        case  FSM_Waiting_For_Terminal_Trigger: Serial.println("FSM_Waiting_For_Terminal_Trigger"); break;
        case  FSM_Waiting_Door_Clear: Serial.println("FSM_Waiting_Door_Clear"); break;
        case  FSM_Waiting_For_Full_Close: Serial.println("FSM_Waiting_For_Full_Close"); break;
        case  FSM_Testing_Loop: Serial.println("FSM_Testing_Loop"); break;
        default: break;
        }
  }
}
//__________________________________________________________________________________________________________________________________________________________________________________
  void door::read_home_swicth(void)
  {
      home_sw_status=digitalRead(Close_Sensor_PIN);
      if(home_sw_status==0)   digitalWrite(LED_Green,LOW);
      else                    digitalWrite(LED_Green,HIGH);
  }
//__________________________________________________________________________________________________________________________________________________________________________________
void door::Simple_Method(void)
{

      if(btn_trig.pressed() || (btn_outSide.pressed()))
      {
          Serial.println("Button Pressed...");
          bzr.beep();
          delay(1000); 
          /////////////////////
          test_open(5700);
          delay(5000);
          // test_close(4800);
          set_door_close();
          t1.target_count(10);


/// INIT JOG
   motor.updateDutyCycle(10);
   motor.enable();
   delay(1000);

    //////////ACL
    temp=15;
    do
    {
   motor.updateDutyCycle(temp);
   motor.enable();
   delay(250);
   temp +=5;

    }while(temp<=30);
  ////////////////////

  // JOG
  delay(3000);
  ///////////////////


 //////////ACL
    temp=30;
    do
    {
      motor.updateDutyCycle(temp);
      motor.enable();
      delay(250);
      temp -=5;
    }while(temp>=10);
  ////////////////////

    digitalWrite(LED_Yellow,LOW);
         while(!door_closed());
         {
           read_home_swicth();
         }
        motor.updateDutyCycle(0);
        digitalWrite(LED_Yellow,HIGH);
   
      }
      else
      {
        Serial3.print("\rFSM_Wait_For_Trigger="); Serial3.print(state_count);state_count++;
      }
}
//__________________________________________________________________________________________________________________________________________________________________________________
void door:: trigger_calling_bell(void)
{
    digitalWrite(Calling_Bell_Trigger,LOW);
    delay(100);
    digitalWrite(Calling_Bell_Trigger,HIGH);
}
//__________________________________________________________________________________________________________________________________________________________________________________
void door:: Handle_loop(void) 
{
  cmd.handle();
  if(cmd.available()) {
    action_for_command(cmd.parsedParts);
    }
  st.blink();
  handle();
  /////////////////////
  if(Serial3.available()) 
  {  // Read all available data
        char receivedChar = Serial3.read();

        if (receivedChar == '\n') 
        { // Message complete
            Serial.print("Full Message Received: ");
            Serial.println(receivedDataMega);

            StaticJsonDocument<256> doc; // Create JSON document (adjust size as needed)
    
            DeserializationError error = deserializeJson(doc, receivedDataMega);
            receivedDataMega = ""; // Clear buffer    
            
            if (error) {
                Serial.print("JSON Parsing Error: ");
                Serial.println(error.c_str());
            }

            // Example: Extracting values from JSON
            const char* command = doc["command"];
            const char* value = doc["value"];

            // // Process the extracted data
            // Serial.print("Command: ");
            // Serial.println(command);
            // Serial.print("Value: ");
            // Serial.println(value);

             // Example: Implementing commands
            if ((strcmp(command, "Door") == 0) && (strcmp(value, "Open") == 0))
            {
                Web_Command="Open";
                receivedDataMega = ""; // Clear buffer    
            } 
        }
        else 
        {
            receivedDataMega += receivedChar; // Append to buffer
         //   Serial.print(receivedDataMega);
        }
    
}
}
///////////////////////////////////////////////

// // Function to parse JSON string
// StaticJsonDocument<256> parseJSON(String jsonString) 
// {
//     StaticJsonDocument<256> doc; // Create JSON document (adjust size as needed)
    
//     DeserializationError error = deserializeJson(doc, jsonString);
//     if (error) {
//         Serial.print("JSON Parsing Error: ");
//         Serial.println(error.c_str());
//     }
    
//     return doc;  // Return the parsed JSON object

//     // Example: Extracting values from JSON
//     const char* command = doc["command"];
//     int value = doc["value"];

//     // Process the extracted data
//     Serial.print("Command: ");
//     Serial.println(command);
//     Serial.print("Value: ");
//     Serial.println(value);
    
//     // Example: Implementing commands
//     if (strcmp(command, "LED_ON") == 0) {
//         digitalWrite(13, HIGH);
//         Serial.println("LED turned ON");
//     } else if (strcmp(command, "LED_OFF") == 0) {
//         digitalWrite(13, LOW);
//         Serial.println("LED turned OFF");
//     }
// }






