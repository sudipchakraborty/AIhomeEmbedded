#ifndef BRD_TIMERMODULE_H
#define BRD_TIMERMODULE_H

#include <Arduino.h>

class BRD_TimerModule {
public:
    BRD_TimerModule();
    void begin();
    void update();
    void FSM_Handler(void);
};

#endif // BRD_TIMERMODULE_H
