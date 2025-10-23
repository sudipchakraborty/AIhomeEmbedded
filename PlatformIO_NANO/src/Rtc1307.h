#ifndef RTC1307_H
#define RTC1307_H

#include <Arduino.h>
#include <Wire.h>
#include <RTClib.h>

/**
 * @brief Simple DS1307 RTC wrapper using Adafruit RTClib.
 *
 * Provides initialization, reading, formatting, and writing convenience methods
 * for the DS1307 RTC module.
 */
class Rtc1307 {
public:
    /**
     * @brief Construct a new Rtc1307 object.
     *
     * Constructor does not initialize I2C hardware. Call begin() in setup().
     */
    Rtc1307();

    /**
     * @brief Initialize Wire/I2C and the DS1307 RTC.
     *
     * @return true if RTC was detected (rtc.begin() returned true)
     * @return false if RTC was not found
     */
    bool begin();

    /**
     * @brief Check whether RTC oscillator is running.
     *
     * Note: this function is non-const because RTClib's isrunning() is non-const.
     *
     * @return true when RTC reports running
     * @return false when RTC not initialized or not running
     */
    bool isRunning();

    /**
     * @brief Get current DateTime from RTC.
     *
     * @return DateTime current value; returns DateTime( (uint32_t)0 ) if RTC not initialized.
     */
    DateTime now();

    /**
     * @brief Return current time formatted as "HH:MM:SS".
     *
     * @return String "HH:MM:SS" or empty String if RTC not initialized.
     */
    String readTimeString();

    /**
     * @brief Return current date/time formatted as "YYYY-MM-DD HH:MM:SS".
     *
     * @return String or empty String if RTC not initialized.
     */
    String readDateTimeString();

    /**
     * @brief Set RTC date/time using RTClib DateTime.
     *
     * @param dt DateTime object
     * @return true if RTC adjusted (initialized), false otherwise
     */
    bool setDateTime(const DateTime &dt);

    /**
     * @brief Set RTC date/time using individual components.
     *
     * @param year Full year, e.g. 2025
     * @param month Month 1..12
     * @param day Day 1..31
     * @param hour Hour 0..23
     * @param minute Minute 0..59
     * @param second Second 0..59
     * @return true if RTC adjusted (initialized), false otherwise
     */
    bool setDateTime(uint16_t year, uint8_t month, uint8_t day,
                     uint8_t hour, uint8_t minute, uint8_t second);

    /**
     * @brief If RTC is present but not running, set it to the compile time.
     *
     * Useful in setup() to recover from RTC without battery.
     *
     * @return true if RTC present (and adjusted if it was stopped), false if RTC not present
     */
    bool updateIfStopped();

private:
    RTC_DS1307 rtc;   ///< RTClib DS1307 object
    bool _initialized;///< true after successful begin()
};

#endif // RTC1307_H
