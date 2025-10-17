#ifndef IRCUT_H
#define IRCUT_H
#include <Arduino.h>

class ircut{

  private:
  byte FSM;
    
  public:
    ircut();
    void begin(void);   
    void FSM_Handler(void);
};





#endif