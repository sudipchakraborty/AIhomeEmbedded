#include "TimeModule.h"

TimeModule::TimeModule() {
    startTime = 0;
    timeoutValue = 0;
    timerRunning = false;
}

void TimeModule::time_reset() {
    startTime = 0;
    timerRunning = false;
}

void TimeModule::time_start() {
    startTime = millis();
    timerRunning = true;
}

void TimeModule::set_time(unsigned long timeout) {
    timeoutValue = timeout;
}

bool TimeModule::timeOut() {
    if (timerRunning && (millis() - startTime >= timeoutValue)) {
        timerRunning = false;
        return true;
    }
    return false;
}
