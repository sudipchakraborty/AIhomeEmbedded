#ifndef TIME_H
#define TIME_H
//////////////
#include <Arduino.h>

//_______________________________________________________________________________________________________
/**
 * @class Time
 * @brief A lightweight non-blocking software timer using Arduino's millis().
 *
 * The `Time` class provides simple timer functionality for embedded applications.
 * It allows you to start, stop, reset, and check timeouts without blocking the CPU.
 * 
 * Typical usage:
 * @code
 * Time timer;
 * timer.set_time(5000);  // Set timeout to 5 seconds
 * timer.time_start();    // Start timer
 *
 * if (timer.timeOut()) {
 *     Serial.println("Timeout occurred!");
 * }
 * @endcode
 */
class Time {
public:
    /**
     * @brief Constructs a new Time object and initializes internal variables.
     *
     * Sets default values for start time, timeout duration, and timer state.
     * The timer does not start automatically after creation.
     */
    Time();

    /**
     * @brief Resets the timer to its initial (stopped) state.
     *
     * Clears the start time and marks the timer as not running.
     * The timeout value remains unchanged.
     */
    void time_reset();

    /**
     * @brief Starts the timer if it is not already running.
     *
     * Records the current system time from `millis()` as the start time.
     * If the timer is already active, this function does nothing.
     */
    void time_start();

    /**
     * @brief Sets the timeout duration for the timer.
     *
     * Defines how long (in milliseconds) the timer should run before a timeout occurs.
     *
     * @param timeout Timeout value in milliseconds.
     */
    void set_time(unsigned long timeout);

    /**
     * @brief Checks if the configured timeout period has elapsed.
     *
     * Compares the elapsed time since @ref time_start() with the set timeout.
     * Once the timeout occurs, the timer automatically stops.
     *
     * @return `true` if the timeout duration has been reached, otherwise `false`.
     */
    bool timeOut();

    /**
     * @brief Returns the elapsed time since the timer started.
     *
     * Calculates how many milliseconds have passed since the last call to @ref time_start().
     *
     * @return Elapsed time in milliseconds. Returns 0 if the timer is not running.
     */
    unsigned long elapsed_time(void);

private:
    unsigned long startTime;     ///< System time (ms) when timer started.
    unsigned long timeoutValue;  ///< Duration (ms) after which timeout occurs.
    bool timerRunning;           ///< Indicates whether the timer is currently running.
};
//_______________________________________________________________________________________________________
#endif
