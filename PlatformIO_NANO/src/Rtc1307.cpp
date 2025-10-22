#include "Rtc1307.h"

/**
 * @brief Construct a new Rtc1307::Rtc1307 object
 */
Rtc1307::Rtc1307() : _initialized(false) {}

/**
 * @brief Initialize Wire/I2C and the DS1307 RTC.
 * @return true if rtc.begin() succeeded
 * @return false otherwise
 */
bool Rtc1307::begin() {
  Wire.begin();
  // try to initialize RTC
  _initialized = rtc.begin();
  return _initialized;
}

/**
 * @brief Check whether RTC oscillator is running.
 *
 * @return true if rtc is present and running
 * @return false otherwise
 */
bool Rtc1307::isRunning() const {
  if (!_initialized) return false;
  return rtc.isrunning();
}

/**
 * @brief Read current DateTime from RTC.
 *
 * @return DateTime current value, or DateTime(0) if RTC not initialized.
 */
DateTime Rtc1307::now() {
  if (!_initialized) return DateTime(0);
  return rtc.now();
}

/**
 * @brief Read current time as "HH:MM:SS".
 *
 * @return String formatted time, or empty string if RTC not initialized.
 */
String Rtc1307::readTimeString() {
  if (!_initialized) return String();
  DateTime t = rtc.now();
  char buf[16];
  snprintf(buf, sizeof(buf), "%02u:%02u:%02u", t.hour(), t.minute(), t.second());
  return String(buf);
}

/**
 * @brief Read current date/time as "YYYY-MM-DD HH:MM:SS".
 *
 * @return String formatted date-time, or empty string if RTC not initialized.
 */
String Rtc1307::readDateTimeString() {
  if (!_initialized) return String();
  DateTime t = rtc.now();
  char buf[32];
  snprintf(buf, sizeof(buf), "%04u-%02u-%02u %02u:%02u:%02u",
           t.year(), t.month(), t.day(), t.hour(), t.minute(), t.second());
  return String(buf);
}

/**
 * @brief Set the DS1307 RTC using a DateTime object.
 *
 * @param dt DateTime value to write
 * @return true if RTC present and adjusted, false if rtc not initialized
 */
bool Rtc1307::setDateTime(const DateTime &dt) {
  if (!_initialized) return false;
  rtc.adjust(dt);
  return true;
}

/**
 * @brief Set the DS1307 RTC using individual components.
 *
 * @param year Full year (e.g., 2025)
 * @param month Month 1..12
 * @param day Day 1..31
 * @param hour Hour 0..23
 * @param minute Minute 0..59
 * @param second Second 0..59
 * @return true if RTC present and adjusted, false otherwise
 */
bool Rtc1307::setDateTime(uint16_t year, uint8_t month, uint8_t day,
                          uint8_t hour, uint8_t minute, uint8_t second) {
  if (!_initialized) return false;
  DateTime dt(year, month, day, hour, minute, second);
  rtc.adjust(dt);
  return true;
}

/**
 * @brief If RTC is stopped, update to compile time.
 *
 * Useful in setup():
 *   if (!rtc.isrunning()) rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
 *
 * @return true if RTC is now running or was already running; false if RTC not present.
 */
bool Rtc1307::updateIfStopped() {
  if (!_initialized) return false;
  if (!rtc.isrunning()) {
    // set to compile time
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
  return true;
}
