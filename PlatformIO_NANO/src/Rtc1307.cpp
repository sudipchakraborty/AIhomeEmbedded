#include "Rtc1307.h"

Rtc1307::Rtc1307() : _initialized(false) {}

/**
 * @brief Initialize I2C and RTC.
 */
bool Rtc1307::begin() {
    Wire.begin();
    _initialized = rtc.begin();
    return _initialized;
}

/**
 * @brief Check whether RTC oscillator is running.
 */
bool Rtc1307::isRunning() {
    if (!_initialized) return false;
    return rtc.isrunning();
}

/**
 * @brief Read current DateTime from RTC.
 *
 * If RTC not initialized, returns DateTime((uint32_t)0) to avoid ambiguity.
 */
DateTime Rtc1307::now() {
    if (!_initialized) return DateTime((uint32_t)0);
    return rtc.now();
}

/**
 * @brief Read time as HH:MM:SS string.
 */
String Rtc1307::readTimeString() {
    if (!_initialized) return String();
    DateTime t = rtc.now();
    char buf[16];
    snprintf(buf, sizeof(buf), "%02u:%02u:%02u", t.hour(), t.minute(), t.second());
    return String(buf);
}

/**
 * @brief Read date and time as "YYYY-MM-DD HH:MM:SS".
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
 * @brief Set RTC using DateTime object.
 */
bool Rtc1307::setDateTime(const DateTime &dt) {
    if (!_initialized) return false;
    rtc.adjust(dt);
    return true;
}

/**
 * @brief Set RTC using individual components.
 */
bool Rtc1307::setDateTime(uint16_t year, uint8_t month, uint8_t day,
                          uint8_t hour, uint8_t minute, uint8_t second) {
    if (!_initialized) return false;
    DateTime dt(year, month, day, hour, minute, second);
    rtc.adjust(dt);
    return true;
}

/**
 * @brief If RTC is stopped, set it to compile time.
 */
bool Rtc1307::updateIfStopped() {
    if (!_initialized) return false;
    if (!rtc.isrunning()) {
        rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    }
    return true;
}
