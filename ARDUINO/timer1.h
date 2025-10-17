#ifndef TIMER1_H
#define TIMER1_H

#include <Arduino.h>

class timer1 {
public:
    timer1();
    void init(long milliseconds);
    void enable();
    void disable();
    void target_count(long milliseconds);
    void reset();

private:
    long getValFromMilliseconds(long milliseconds);

public:
    volatile bool completed;
    volatile long countReg;
    volatile long targetVal;
};

// Declare a global instance of Timer1
extern timer1 t1;

#endif
