#ifndef TIMEMODULE_H
#define TIMEMODULE_H

#include <Arduino.h>

class TimeModule {
public:
    TimeModule();

    void time_reset();                     // Reset timer
    void time_start();                     // Start timer
    void set_time(unsigned long timeout);  // Set timeout in milliseconds
    bool timeOut();                        // Check if timeout occurred

private:
    unsigned long startTime;
    unsigned long timeoutValue;
    bool timerRunning;
};

#endif



 