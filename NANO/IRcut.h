#ifndef IRCUT_H
#define IRCUT_H
#include <Arduino.h>

class ircut{

  private:
  
    
  public:
    byte FSM;
    ircut();
    void begin(void);   
    void FSM_Handler(void);

  enum state {
    start,
    wait_for_any_trigger,
    wait_for_outside_trigger,
    wait_for_inside_trigger,
    load_on,
    wait_for_release,
    status_send_log
  };
};
#endif