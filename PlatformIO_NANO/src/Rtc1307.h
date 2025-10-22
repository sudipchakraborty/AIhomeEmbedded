#ifndef Rtc1307_h
#define Rtc1307_h

#include <Arduino.h>
#include <Wire.h>
#include <RTClib.h>

/**
 * @file Rtc1307.h
 * @brief Simple DS1307 RTC wrapper using Adafruit RTClib.
 * This class wraps common DS1307 operations: initialization, reading current time,
 * formatting time/date strings, and updating the RTC clock.
 */
class Rtc1307 {
public:
  /**
   * @brief Construct a new Rtc1307 object.
   * Does not initialize I2C or the RTC hardware — call begin() in setup().
   */
  Rtc1307();

  /**
   * @brief Initialize Wire and the DS1307 RTC.
   * Should be called from setup(). Returns true if RTC was detected.
   * @return true RTC begin success
   * @return false RTC begin failed
   */
  bool begin();

  /**
   * @brief Check whether RTC oscillator is running.
   * @return true if RTC reports running
   * @return false if RTC not running or not initialized
   */
  bool isRunning() const;

  /**
   * @brief Read current DateTime from the RTC.
   * @return DateTime current RTC date/time. If RTC not initialized, returns DateTime(0).
   */
  DateTime now();

  /**
   * @brief Read current time as HH:MM:SS string.
   * Example: "18:05:03"
   * @return String formatted time
   */
  String readTimeString();

  /**
   * @brief Read current date and time as "YYYY-MM-DD HH:MM:SS".
   * Example: "2025-10-22 18:05:03"
   * @return String formatted date-time
   */
  String readDateTimeString();

  /**
   * @brief Set the RTC using a RTClib DateTime object.
   * @param dt DateTime to set the RTC to
   * @return true if write succeeded (rtc present)
   * @return false if rtc not initialized
   */
  bool setDateTime(const DateTime &dt);

  /**
   * @brief Set the RTC using individual components.
   * @param year Full year (e.g., 2025)
   * @param month Month 1..12
   * @param day Day 1..31
   * @param hour Hour 0..23
   * @param minute Minute 0..59
   * @param second Second 0..59
   * @return true if write succeeded
   */
  bool setDateTime(uint16_t year, uint8_t month, uint8_t day,
                   uint8_t hour, uint8_t minute, uint8_t second);

  /**
   * @brief If RTC is stopped, set it to the compile time (useful in setup).
   * This calls rtc.adjust(DateTime(F(__DATE__), F(__TIME__))) if RTC is present but not running.
   * Returns true if the RTC was running already or was successfully updated.
   */
  bool updateIfStopped();

private:
  RTC_DS1307 rtc;       ///< RTClib RTC object for DS1307
  bool _initialized;    ///< True after successful begin()
};

#endif // Rtc1307_h
