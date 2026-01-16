#ifndef IRCUT_H
#define IRCUT_H
#include <Arduino.h>
////////////////////
#define Out_ON    1
#define Out_OFF   2
#define In_ON     3
#define In_OFF    4
////////////////////
class ircut{
  private:
    byte event_count;
    byte event_val;
    void event_clear(void);
    byte sensor_state_backup;
    byte sensor_state_current;
    long v_delay_reg=0;
  public:
    byte FSM;
    ircut();
    void begin(void);   
    void FSM_Handler(void);
    void Sensor_Read(void);
    void CheckTimeOut(void);
    void LoadTrigger(void); 
    void Check_Sensor(void);
    void Check_Sensor2(void);
    void PWM_setup(void);
    void PWM_burst_task(void);
    void setup_timer2_38kHz(void);
    void setup_timer1_burst(void);
    void device_self_test(void);
    void sensor_health_check(void);
    void event_detect(void);
    bool OutSide_sensor_error=true;
    bool InSide_sensor_error=true;
    bool Sensor_Health=false;
  enum state {
    start,
    idle,
    check_for_valid_IN,
    validate_IN,
    check_for_valid_out,
    validate_Out
  };
};
#endif