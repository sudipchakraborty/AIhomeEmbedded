 #ifndef DOOR_H
 #define DOOR_H
 #include <Arduino.h>
//////////////////
class door
{
    public:
    door();
    void init(void);
    void handle(void);
    void set_door_open(void);
    void set_door_close(void);
    bool door_not_closed(void);
    bool door_closed(void);
    bool door_opened(void);
    void PrintSensorStatus(void);
    void test_open(unsigned int duration);
    void test_close(unsigned int duration);
    void action_for_command(String *cmd);
    void read_home_swicth(void);
    void Simple_Method(void);
    void trigger_calling_bell(void);
    String Web_Command="";

    void Handle_loop(void); 
    ////////////////////////
    private:
    bool JoG_Completed(unsigned int val_inc, unsigned int val_cmp);
    void setUpTimer1(long milliseconds);
    char FSM;
    int  Waiting_Count;
    long accl_count_reg;
    long jog_count_reg;
    long temp;
    int TestCount;
    char door_Activity;
    int loop_test_count;
    bool home_sw_status;
    unsigned int bzr_interval;


};


enum FSM
{
  FSM_Idle,
  FSM_Init,
  FSM_check_door_open,
  FSM_Wait_For_Full_Close,
  FSM_Wait_For_Open_Sensor_trigger,
  FSM_Wait_For_Close_Sensor_Trigger,
  FSM_Wait_For_Trigger,
  FSM_Initial_Jogg,
  FSM_Acceleration,
  FSM_Jog,
  FSM_Deceleration,
  FSM_Final_Jogg,
  FSM_Waiting_For_Terminal_Trigger,
  FSM_Waiting_Door_Clear,
  FSM_Waiting_For_Full_Close,
  FSM_Testing_Loop,
  FSM_Waiting_to_Start_Close
};
///////////////////////////////////////
#define  Tick  1000
#define dc_start   5 
#define  motor_start_jog    250 
#define during_accl_count  5000
#define jog_duration      500

#define PIN_DIR   33
#define Dir_Open  0
#define Dir_Close 1

#define Door_Opening   1
#define Door_Closing   2

#define open  1
#define close 2

#define LED_Yellow  25
#define LED_Green   27

#define PIN_sw_door_open  20

//___________________________________________________________________________________________________________________________________________________________
 #endif




 

// #include "motorDC.h"
// ///////////////////////////////////////////////////////////////////////////
// #define PIN_Motor  23
// int count=0;

 
//  pinMode(27, OUTPUT);
//   Serial.begin(115200); 
//  

//   // systemStateHandler();
// //  StatusLED();
