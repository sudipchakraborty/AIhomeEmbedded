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
    wait_for_trigger,
    load_on,
    wait_for_release,
    status_send_log
  };
};
#endif